#include "QvkWatcherPlug.h"

#include <QFile>
#include <QStandardPaths>
/*
 * QvkWatcherPlug monitoring only new or removed Audiodevices from the PulseAudio server.
 * QvkWatcherPlug does not return any devices, if the PulseAudio server start or stop.
 */

QvkWatcherPlug::QvkWatcherPlug(){}
QvkWatcherPlug::~QvkWatcherPlug(){}

static gchar *get_launch_line (GstDevice * device)
{
  static const char *const ignored_propnames[] = { "name", "parent", "direction", "template", "caps", NULL };
  GString *launch_line = NULL;
  GstElement *element;
  GstElement *pureelement;
  GParamSpec **properties, *property;
  GValue value = G_VALUE_INIT;
  GValue pvalue = G_VALUE_INIT;
  guint i, number_of_properties;
  GstElementFactory *factory;

  element = gst_device_create_element( device, NULL );

  if ( !element )
    return NULL;

  factory = gst_element_get_factory( element );
  if ( !factory )
  {
    gst_object_unref( element );
    return NULL;
  }

  if ( !gst_plugin_feature_get_name( factory ) )
  {
    gst_object_unref( element );
    return NULL;
  }

  pureelement = gst_element_factory_create( factory, NULL );

  properties = g_object_class_list_properties( G_OBJECT_GET_CLASS( element ), &number_of_properties );
  if ( properties )
  {
    for ( i = 0; i < number_of_properties; i++ )
    {
      gint j;
      gboolean ignore = FALSE;
      property = properties[i];

      if ( ( property->flags & G_PARAM_READWRITE ) != G_PARAM_READWRITE )
        continue;

      for ( j = 0; ignored_propnames[j]; j++ )
        if ( !g_strcmp0( ignored_propnames[j], property->name ) )
          ignore = TRUE;

      if ( ignore )
        continue;

      g_value_init( &value, property->value_type );
      g_value_init( &pvalue, property->value_type );
      g_object_get_property( G_OBJECT( element ), property->name, &value );
      g_object_get_property( G_OBJECT( pureelement ), property->name, &pvalue );
      if (gst_value_compare( &value, &pvalue ) != GST_VALUE_EQUAL )
      {
        gchar *valuestr = gst_value_serialize( &value );
        if ( !valuestr )
        {
          GST_WARNING( "Could not serialize property %s:%s", GST_OBJECT_NAME( element ), property->name );
          g_free( valuestr );
          goto next;
        }

        launch_line = g_string_new( valuestr );

        g_free( valuestr );
      }

    next:
      g_value_unset( &value );
      g_value_unset( &pvalue );
    }
    g_free( properties );
  }

  gst_object_unref( GST_OBJECT( element ) );
  gst_object_unref( GST_OBJECT( pureelement ) );

  return g_string_free (launch_line, FALSE);
}


static gboolean func( GstBus *bus, GstMessage *message, gpointer user_data )
{
   Q_UNUSED(bus);
   Q_UNUSED(user_data);

   QFile file;
   QString filename = QStandardPaths::writableLocation( QStandardPaths::TempLocation ) + "/vokoscreenAudioPlugFile.txt";
   file.setFileName( filename );
   file.open( QIODevice::WriteOnly | QIODevice::Text );

   GstDevice *gstDevice;
   gchar *name;
   gchar *device;

   switch ( GST_MESSAGE_TYPE( message ) )
   {
     case GST_MESSAGE_DEVICE_ADDED:
       gst_message_parse_device_added( message, &gstDevice );
       name = gst_device_get_display_name( gstDevice );
       qDebug( "[vokoscreen][Audio] device added: %s", name );
       device = get_launch_line( gstDevice );
       qDebug( "[vokoscreen][Audio] device added: %s", device );
       file.write( "[Audio-device-added]\n" );
       file.write( name );
       file.write( "\n" );
       file.write( device );
       file.flush();
       file.close();
       g_free( name );
       g_free( device );
       gst_object_unref( gstDevice );
       break;
     case GST_MESSAGE_DEVICE_REMOVED:
       gst_message_parse_device_removed( message, &gstDevice );
       name = gst_device_get_display_name( gstDevice );
       qDebug( "[vokoscreen][Audio] device removed: %s", name );
       device = get_launch_line( gstDevice );
       qDebug( "[vokoscreen][Audio] device removed: %s", device );
       file.write( "[Audio-device-removed]\n" );
       file.write( name );
       file.write( "\n" );
       file.write( device );
       file.flush();
       file.close();
       g_free( name );
       g_free( device );
       gst_object_unref( gstDevice );
       break;
     default:
       break;
   }

   return G_SOURCE_CONTINUE;
}


GstDeviceMonitor *QvkWatcherPlug::start_monitor()
{
   GstDeviceMonitor *gstDeviceMonitor;
   GstBus *gstBus;
   GstCaps *gstCaps;

   gstDeviceMonitor = gst_device_monitor_new();
   gstBus = gst_device_monitor_get_bus( gstDeviceMonitor );
   gst_bus_add_watch( gstBus, func, nullptr );
   gst_object_unref( gstBus );

   gstCaps = gst_caps_new_empty_simple( "audio/x-raw" );
   gst_device_monitor_add_filter( gstDeviceMonitor, "Audio/Source", gstCaps );
   gst_caps_unref( gstCaps );

   gst_device_monitor_start( gstDeviceMonitor );

   return gstDeviceMonitor;
}


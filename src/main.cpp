#include "mainwindow.h"
#include <QTranslator>
#include <QLibraryInfo>

#include <gst/gst.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Initialize GStreamer
    gst_init (&argc, &argv);

    QTranslator * qtTranslator = new QTranslator();
    qtTranslator->load( "qt_" + QLocale::system().name(), QLibraryInfo::location( QLibraryInfo::TranslationsPath ) );
    app.installTranslator( qtTranslator );

    QTranslator translator;
    translator.load( "vokoscreen_" + QLocale::system().name(), ":/language" );
    app.installTranslator( &translator );

    QvkMainWindow w;
    w.show();

    return app.exec();
}

#ifndef QvkPulseGstr_H
#define QvkPulseGstr_H

#include <gst/gst.h>

#include <QObject>

class QvkPulseGstr: public QObject
{
    Q_OBJECT

public:
    QvkPulseGstr();
    virtual ~QvkPulseGstr();
    QString get_AudioDeviceString( GstDevice *device );

    
public slots:
    QStringList get_all_Audio_devices();


private:
    void print_plugin_info ();

private slots:


protected:
  
  
signals:
    
};

#endif

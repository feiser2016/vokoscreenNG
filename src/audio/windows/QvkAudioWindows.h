#ifndef QvkAudioWindows_H 
#define QvkAudioWindows_H

#include "ui_formMainwindow.h"
#include <QObject>
#include <QTimer>

class QvkAudioWindows: public QObject
{
    Q_OBJECT
    
public:
    QvkAudioWindows(  Ui_formMainWindow *ui_mainwindow );
    virtual ~QvkAudioWindows();

    
public slots:
    void slot_start( bool value );

  
private:
    Ui_formMainWindow *ui;
    QTimer *timer;
    int counter;

    
private slots:
    void slot_getWindowsDevices();
    void slot_clearVerticalLayoutAudioDevices();
    void slot_update();


protected:
  
  
signals:

    
};

#endif

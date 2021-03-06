﻿#include "QvkHelp.h"

#include <QMessageBox>
#include <QLabel>
#include <QDir>
#include <QTextDocument>

QvkHelp::QvkHelp( QMainWindow *mainWindow, Ui_formMainWindow *ui_mainwindow ) : uiFormHelp(new(Ui::formHelp))
{
    connect( mainWindow, SIGNAL( destroyed( QObject*) ), this, SLOT( slot_cleanUp() ) );

    ui = ui_mainwindow;
    uiFormHelp->setupUi( this );

    resize( 800, 600 );
    setWindowTitle( "vokoscreen help" );
    QIcon icon;
    icon.addFile( QString::fromUtf8( ":/pictures/vokoscreen.png" ), QSize(), QIcon::Normal, QIcon::Off );
    setWindowIcon( icon );

    QStringList helpStringList;
    helpStringList << "https:/"
                   << "vokoscreen.volkoh.de"
                   << "3.0"
                   << "help";

    vk_helpPath = helpStringList.join( "/" ).append( "/");
    QString language = "en";
    vk_helpPath = vk_helpPath + language + "/";

    vkDownloadHTML = new QvkDownloader( temporaryDirLocal.path() );
    vkDownloadFiles = new QvkDownloader( temporaryDirLocal.path() );

    QIcon iconHelp = style()->standardIcon( QStyle::SP_MessageBoxInformation );

    // Tab 1
    connect( ui->toolButtonHelpFullscreen, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpFullscreen() ) );
    ui->toolButtonHelpFullscreen->setIcon( iconHelp );

    connect( ui->toolButtonHelpWindow, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpWindow() ) );
    ui->toolButtonHelpWindow->setIcon( iconHelp );

    connect( ui->toolButtonHelpArea, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpArea() ) );
    ui->toolButtonHelpArea->setIcon( iconHelp );

    connect( ui->toolButtonHelpNoMouseCursor, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpNoMouseCursor() ) );
    ui->toolButtonHelpNoMouseCursor->setIcon( iconHelp );

    connect( ui->toolButtonHelpScale, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpScale() ) );
    ui->toolButtonHelpScale->setIcon( iconHelp );

    connect( ui->toolButtonHelpMagnifier, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpMagnifier() ) );
    ui->toolButtonHelpMagnifier->setIcon( iconHelp );

    connect( ui->toolButtonHelpShowclick, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpShowclick() ) );
    ui->toolButtonHelpShowclick->setIcon( iconHelp );

    connect( ui->toolButtonHelpCountdown, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpCountdown() ) );
    ui->toolButtonHelpCountdown->setIcon( iconHelp );

    connect( ui->toolButtonHelpExecute, SIGNAL( clicked( bool ) ), this, SLOT( slot_toolButtonHelpExecute() ) );
    ui->toolButtonHelpExecute->setIcon( iconHelp );

    connect( ui->toolButtonAudioHelp, SIGNAL( clicked( bool ) ), this, SLOT( slot_audioHelp() ) );

    // Tab 2 Audio and Videocodec
    ui->toolButtonFramesHelp->setIcon( iconHelp );
    ui->toolButtonAudioHelp->setIcon( iconHelp );
    ui->toolButtonVideoCodecHelp->setIcon( iconHelp );

    // Tab 3 Time
    ui->toolButtonHelpStartTime->setIcon( iconHelp );
    ui->toolButtonHelpStopRecordingAfter->setIcon( iconHelp );

    // Tab 4 Misc
    ui->toolButtonHelpVideoPath->setIcon( iconHelp );
    ui->toolButtonHelpLimitOfFreeDiskSpace->setIcon( iconHelp );
    ui->toolButtonHelpShowInSystray->setIcon( iconHelp );
    ui->toolButtonHelpMinimizedWhenRecordingStarts->setIcon( iconHelp );
    ui->toolButtonHelpVokoscreenStartsMinimized->setIcon( iconHelp );

    // Tab 5 Available muxer, encoder etc.
    ui->toolButtonAvalaibleHelp->setIcon( iconHelp );

    // Screenshot
    ui->toolButtonHelpScreenshotScreen->setIcon( iconHelp );
    ui->toolButtonHelpScreenshotFullscreen->setIcon( iconHelp  );
    ui->toolButtonHelpScreenshotWindow->setIcon( iconHelp );
    ui->toolButtonHelpScreenshotArea->setIcon( iconHelp );
    ui->toolButtonHelpScreenshotSuffix->setIcon( iconHelp );
    ui->toolButtonHelpScreenshotCountdown->setIcon( iconHelp );
    ui->toolButtonHelpScreenshotHideThisWindow->setIcon( iconHelp );
    ui->toolButtonHelpScreenshotExecute->setIcon( iconHelp );
    ui->toolButtonHelpScreenShotMiscPath->setIcon( iconHelp );

    // Camera
    ui->toolButtonHelpCamera->setIcon( iconHelp );

    // Player
    //ui->toolButtonHelpPlayer->setIcon( iconHelp );

    // Log
    ui->toolButtonHelpReport->setIcon( iconHelp );


    //connect( ui->toolButtonHelpVideoPath, SIGNAL( clicked( bool ) ), this, SLOT( slot_miscHelpVideoPath() ) );
    //connect( ui->toolButtonHelpStartTime, SIGNAL( clicked( bool ) ), this, SLOT( slot_miscHelpStartTime() ) );
    //connect( ui->toolButtonHelpStopRecordingAfter, SIGNAL( clicked( bool ) ), this, SLOT( slot_miscHelpStopRecordingAfter() ) );
    //connect( ui->toolButtonHelpScale, SIGNAL( clicked( bool ) ), this, SLOT( slot_miscHelpScal() ) );
    //connect( ui->toolButtonHelpLimitOfFreeDiskSpace, SIGNAL( clicked( bool ) ), this, SLOT( slot_miscHelpLimitOfFreeDiskSpace() ) );

    //connect( ui->toolButtonAvalaibleHelp, SIGNAL( clicked( bool ) ), this, SLOT( slot_availableHelp() ) );
}


QvkHelp::~QvkHelp()
{
}


void QvkHelp::slot_cleanUp()
{
    temporaryDirLocal.remove();
}


void QvkHelp::slot_toolButtonHelpFullscreen()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpFullscreen.html" );
}


void QvkHelp::slot_toolButtonHelpWindow()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpWindow.html" );
}


void QvkHelp::slot_toolButtonHelpArea()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpArea.html" );
}

void QvkHelp::slot_toolButtonHelpNoMouseCursor()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpNoMouseCursor.html" );
}


void QvkHelp::slot_toolButtonHelpScale()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpScale.html" );
}


void QvkHelp::slot_toolButtonHelpMagnifier()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpMagnifier.html" );
}


void QvkHelp::slot_toolButtonHelpShowclick()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpShowclick.html" );
}


void QvkHelp::slot_toolButtonHelpCountdown()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpCountdown.html" );
}


void QvkHelp::slot_toolButtonHelpExecute()
{
    loadHTML( vk_helpPath + "screencast/toolButtonHelpExecute.html" );
}


void QvkHelp::slot_audioHelp()
{
    loadHTML( vk_helpPath + "screencast/tab2-audio.html" );
}


/*
 * To first we load the html file ...
 */
void QvkHelp::loadHTML( QString value )
{
    QFileInfo fileInfo( value );
    remotePath = fileInfo.path();
    remoteBasename = fileInfo.baseName();
    disconnect( vkDownloadHTML, nullptr, nullptr, nullptr );
    connect( vkDownloadHTML, SIGNAL( signal_fileDownloaded( QString ) ), this, SLOT( slot_parseHTML( QString ) ) );
    vkDownloadHTML->doDownload( value );
}


bool QvkHelp::isFileInLine( QString line )
{
    bool value = false;
    for ( int i = 0; i < toDownloadFiles.count(); i++ )
    {
        if ( line.contains( toDownloadFiles.at(i), Qt::CaseInsensitive ) )
        {
            value = true;
            break;
        }
        else
        {
            value = false;
        }
    }
    return value;
}


int QvkHelp::getCountFileToDownload( QString tempPathFileName )
{
    QFile file( tempPathFileName );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::information( nullptr, "Help error", file.errorString() );
    }

    int count = 0;
    QTextStream textStream( &file );
    while( !textStream.atEnd() )
    {
        QString line = textStream.readLine();
        if ( isFileInLine( line ) )
        {
            count++;
        }
    }
    file.close();
    return count;
}


/*
 * ... then we parse *.html of files and download all files from remote Url and save local in tmp ...
 */
void QvkHelp::slot_parseHTML( QString tempPathFileName )
{
    localFiles.clear();
    localFiles << tempPathFileName;

    QFileInfo fileInfo( tempPathFileName );
    QString tmpPath = fileInfo.absolutePath();


    QFile file( tempPathFileName );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::information( nullptr, "error", file.errorString() );
    }

    int countFiles = getCountFileToDownload( tempPathFileName );
    qDebug() << "[vokoscreen] HTML file parsed, downloading" << countFiles << "files";
    int counter = 0;
    QTextStream textStream( &file );
    while( !textStream.atEnd() )
    {
        QString line = textStream.readLine();
        if ( isFileInLine( line ) )
        {
            QString fileForHTML = line.section( "\"", 1, 1 );
            counter++;
            if ( counter == countFiles )
            {
                disconnect( vkDownloadFiles, nullptr, nullptr, nullptr );
                connect( vkDownloadFiles, SIGNAL( signal_fileDownloaded( QString ) ), this, SLOT( slot_showHelp( QString ) ) );
            }
            vkDownloadFiles->doDownload( remotePath + "/" + fileForHTML );
            localFiles << tmpPath + + "/" + fileForHTML;
        }
    }

    if ( counter == 0 )
    {
        // "dummy.png" is a fake, we need this if no file is downlowded
        slot_showHelp( tmpPath + "/" + "dummy.png");
    }

    file.close();
}

/*
 * ... then we show the html file
 */
void QvkHelp::slot_showHelp( QString tempPathFileName )
{
    QDir dir;
    QString currentdir = dir.currentPath();

    QFileInfo fileInfo( tempPathFileName );
    QString tmpPath = fileInfo.absolutePath();
    dir.setCurrent( tmpPath );

    QString htmlFile = tmpPath + "/" + remoteBasename + ".html";
    QFile file( htmlFile );
    if( !file.open( QIODevice::ReadOnly ) )
    {
        QMessageBox::information( nullptr, "error", file.errorString() );
    }

    QTextStream textStream( &file );
    QString value = textStream.readAll();

    // Antialiasing for Font
    QFont font = uiFormHelp->textBrowser->font();
    font.setStyleStrategy( QFont::PreferAntialias );
    uiFormHelp->textBrowser->setFont(font);

    uiFormHelp->textBrowser->setText( value );
    file.close();

    show();
    qDebug() << "[vokoscreen] Show help";

    dir.setCurrent( currentdir );

    // remove all tmp files
    for ( int i = 0; i < localFiles.count(); i++  )
    {
        QFile file( localFiles.at( i ) );
        file.remove();
    }
}


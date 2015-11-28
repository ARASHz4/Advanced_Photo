#include "advancedphoto.h"

#include <QSettings>
#include <QTranslator>
#include <QMessageBox>
#include <QFileOpenEvent>
#include <QUrl>

#include <QDebug>

AdvancedPhoto::AdvancedPhoto(int argc, char *argv[]) : QApplication(argc, argv)
{
    args = AdvancedPhoto::arguments();
    args.removeAt(0);
}

bool AdvancedPhoto::event(QEvent *event)
{
    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
        args << openEvent->file();
    }

    if(args.count() > 0)
    {
        photowindow.OpenArguments(args);
        args.clear();
    }

    return QApplication::event(event);
}

void AdvancedPhoto::StartApp()
{
    bool debug = true/*false*/;

    if(debug == false)
    {
        QString Message;

    #if defined(Q_OS_WIN)
        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/printsupport/windowsprintersupport.dll").isFile())
        {
            Message = Message + "\n" + "windowsprintersupport.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qdds.dll").isFile())
        {
            Message = Message + "\n" + "qdds.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qgif.dll").isFile())
        {
            Message = Message + "\n" + "qgif.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qicns.dll").isFile())
        {
            Message = Message + "\n" + "qicns.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qico.dll").isFile())
        {
            Message = Message + "\n" + "qico.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qjp2.dll").isFile())
        {
            Message = Message + "\n" + "qjp2.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qjpeg.dll").isFile())
        {
            Message = Message + "\n" + "qjpeg.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qmng.dll").isFile())
        {
            Message = Message + "\n" + "qmng.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qsvg.dll").isFile())
        {
            Message = Message + "\n" + "qsvg.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qtga.dll").isFile())
        {
            Message = Message + "\n" + "qtga.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qtiff.dll").isFile())
        {
            Message = Message + "\n" + "qtiff.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qwbmp.dll").isFile())
        {
            Message = Message + "\n" + "qwbmp.dll";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/imageformats/qwebp.dll").isFile())
        {
            Message = Message + "\n" + "qwebp.dll";
        }
    #elif defined(Q_OS_MAC)
        QStringList CD (QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath().split("/"));
        QString Back;
        for(int i=0; i<CD.count()-1; i++)
        {
            if(i == 0)
            {
                Back = CD[i];
            }
            else
            {
                Back = Back + "/" + CD[i];
            }
        }
        QString PlugIns = Back + "/PlugIns";

        if(!QFileInfo(PlugIns + "/printsupport/libcocoaprintersupport.dylib").isFile())
        {
            Message = Message + "\n" + "libcocoaprintersupport.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqdds.dylib").isFile())
        {
            Message = Message + "\n" + "libqdds.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqgif.dylib").isFile())
        {
            Message = Message + "\n" + "libqgif.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqicns.dylib").isFile())
        {
            Message = Message + "\n" + "libqicns.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqico.dylib").isFile())
        {
            Message = Message + "\n" + "libqico.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqjp2.dylib").isFile())
        {
            Message = Message + "\n" + "libqjp2.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqjpeg.dylib").isFile())
        {
            Message = Message + "\n" + "libqjpeg.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqmng.dylib").isFile())
        {
            Message = Message + "\n" + "libqmng.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqtga.dylib").isFile())
        {
            Message = Message + "\n" + "libqtga.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqtiff.dylib").isFile())
        {
            Message = Message + "\n" + "libqtiff.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqwbmp.dylib").isFile())
        {
            Message = Message + "\n" + "libqwbmp.dylib";
        }

        if(!QFileInfo(PlugIns + "/imageformats/libqwebp.dylib").isFile())
        {
            Message = Message + "\n" + "libqwebp.dylib";
        }
    #elif defined(Q_OS_LINUX)
        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/platforms/libqxcb.so").isFile())
        {
            Message = Message + "\n" + "libqxcb.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/platformthemes/libqgtk2.so").isFile())
        {
            Message = Message + "\n" + "libqgtk2.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/printsupport/libcupsprintersupport.so").isFile())
        {
            Message = Message + "\n" + "libcupsprintersupport.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqdds.so").isFile())
        {
            Message = Message + "\n" + "libqdds.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqgif.so").isFile())
        {
            Message = Message + "\n" + "libqgif.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqicns.so").isFile())
        {
            Message = Message + "\n" + "libqicns.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqico.so").isFile())
        {
            Message = Message + "\n" + "libqico.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqjp2.so").isFile())
        {
            Message = Message + "\n" + "libqjp2.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqjpeg.so").isFile())
        {
            Message = Message + "\n" + "libqjpeg.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqmng.so").isFile())
        {
            Message = Message + "\n" + "libqmng.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqsvg.so").isFile())
        {
            Message = Message + "\n" + "libqsvg.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqtga.so").isFile())
        {
            Message = Message + "\n" + "libqtga.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqtiff.so").isFile())
        {
            Message = Message + "\n" + "libqtiff.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqwbmp.so").isFile())
        {
            Message = Message + "\n" + "libqwbmp.so";
        }

        if(!QFileInfo(QFileInfo(AdvancedPhoto::arguments()[0]).absolutePath() + "/plugins/imageformats/libqwebp.so").isFile())
        {
            Message = Message + "\n" + "libqwebp.so";
        }
    #endif

        if(!Message.isEmpty())
        {
            QMessageBox *msg = new QMessageBox;
            msg->setIcon(QMessageBox::Critical);
            msg->setWindowTitle(AdvancedPhoto::applicationName() + " Error");
            msg->setWindowIcon(QIcon(":/Icons/Small Icon.png"));
            msg->setText("The application can't start because some files is missing from your computer.");
            msg->setInformativeText("Try reinstalling the application to fix this problem.");
            msg->setDetailedText("This files is missing :" + Message);
            msg->setStandardButtons(QMessageBox::Ok);
            msg->setDefaultButton(QMessageBox::Ok);
            msg->exec();

            exit(1);
        }
    }

    //Load Option
    {
        extern bool kar, sgf, oap, sam;
        extern int SlideshowSpeed, ScreenshotDelay;

        QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
        SettingsAP.beginGroup("Option");

        //Keep Aspect Ratio
        {
            if( (QString(SettingsAP.value("KeepAspectRatio").toString()).isEmpty())
                    || (QString(SettingsAP.value("KeepAspectRatio").toString())!="true"
                        && QString(SettingsAP.value("KeepAspectRatio").toString())!="false"))
            {
                SettingsAP.setValue("KeepAspectRatio", "true");
            }

            kar = SettingsAP.value("KeepAspectRatio").toBool();
        }

        //Load Photos Folder
        {
            if( (QString(SettingsAP.value("LoadPhotosFolder").toString()).isEmpty())
                    || (QString(SettingsAP.value("LoadPhotosFolder").toString())!="true"
                        && QString(SettingsAP.value("LoadPhotosFolder").toString())!="false"))
            {
                SettingsAP.setValue("LoadPhotosFolder", "true");
            }

            oap = SettingsAP.value("LoadPhotosFolder").toBool();
        }

        //Language
        {
            QTranslator *Language = new QTranslator;

            if(SettingsAP.value("Language").toString() == "English")
            {
                Language->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Language);
                AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
            }
            else if(SettingsAP.value("Language").toString() == "پارسی")
            {
                Language->load(":/Language/Persian.qm");
                AdvancedPhoto::installTranslator(Language);
                AdvancedPhoto::setLayoutDirection(Qt::RightToLeft);
            }
            else if(SettingsAP.value("Language").toString() == "Español")
            {
                Language->load(":/Language/Spanish.qm");
                AdvancedPhoto::installTranslator(Language);
                AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
            }
            else if(SettingsAP.value("Language").toString() == "中國傳統")
            {
                Language->load(":/Language/Traditional Chinese.qm");
                AdvancedPhoto::installTranslator(Language);
                AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
            }
            else
            {
                SettingsAP.setValue("Language", "English");

                Language->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Language);
                AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
            }
        }

        //Slideshow
        {
            SlideshowSpeed = SettingsAP.value("SlideshowSpeed").toInt();

            if(SlideshowSpeed <= 0 || SlideshowSpeed > 99)
            {
                SlideshowSpeed = 2;

                SettingsAP.setValue("SlideshowSpeed",SlideshowSpeed);
            }

            if((QString(SettingsAP.value("SlideshowFullscreen").toString()).isEmpty())
                    || (QString(SettingsAP.value("SlideshowFullscreen").toString())!="true"
                        && QString(SettingsAP.value("SlideshowFullscreen").toString())!="false"))
            {
                SettingsAP.setValue("SlideshowFullscreen", "false");
            }

            sgf = SettingsAP.value("SlideshowFullscreen").toBool();
        }

        //Screenshot
        {
            ScreenshotDelay = SettingsAP.value("ScreenshotDelay").toInt();

            if(ScreenshotDelay < 0 || ScreenshotDelay > 60)
            {
                ScreenshotDelay = 3;

                SettingsAP.setValue("ScreenshotDelay",ScreenshotDelay);
            }

            if((QString(SettingsAP.value("ScreenshotAtuoMinimize").toString()).isEmpty())
                    || (QString(SettingsAP.value("ScreenshotAtuoMinimize").toString())!="true"
                        && QString(SettingsAP.value("ScreenshotAtuoMinimize").toString())!="false"))
            {
                SettingsAP.setValue("ScreenshotAtuoMinimize", "true");
            }

            sam = SettingsAP.value("ScreenshotAtuoMinimize").toBool();
        }

        SettingsAP.endGroup();
    }

    photowindow.show();
}

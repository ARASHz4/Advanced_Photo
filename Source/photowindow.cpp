#include "photowindow.h"
#include "ui_photowindow.h"
#include "advancedphoto.h"
#include "option.h"
#include "resizephoto.h"
#include "photoinfo.h"
#include "about.h"

#include <QPixmap>
#include <QImage>
#include <QScreen>
#include <QSettings>
#include <QTranslator>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QUrl>
#include <QIcon>
#include <QMouseEvent>
#include <QMimeData>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QMenu>
#include <QDesktopServices>
#include <QUuid>

#include <QDebug>

//Variables:
QStringList PhotoAddress;
QString ScreenshotFile;
QString PSize;
extern int SlideshowSpeed, ScreenshotDelay;
extern int RSWidth;
extern int RSHeight;
extern bool kar, sgf, oap, resz, rekar, sam;
bool zoom=false, sls=false, pe=false, sph=false, ssh=false ,iif=false , wasMax=false;
int ps=0, pst=0, psb=0;
int pw,ph,ww,wh,j,mbh,tbh;
int pw2,ph2;
int pwz=0,phz=0;
int SaveAnswer;
int rd=0, zoomp=0;
float zw,zh;
int IconTrayNum=0;
//

PhotoWindow::PhotoWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::PhotoWindow)
{
    ui->setupUi(this);

    //ToolBar & Action Setting
    {
        ui->toolBar->setContextMenuPolicy(Qt::PreventContextMenu);

        if(PhotoAddress.count() <= 1)
        {
            ui->actionNext_Photo->setEnabled(false);
            ui->actionPrevious_Photo->setEnabled(false);
            ui->actionSlideshow->setEnabled(false);
        }
        if(pe == false)
        {
            ui->actionSave->setEnabled(false);
            ui->actionSave_As->setEnabled(false);
            ui->actionClose_Photo->setEnabled(false);
            ui->actionPrint->setEnabled(false);
            ui->actionResize->setEnabled(false);
            ui->actionRotateLeft->setEnabled(false);
            ui->actionRotateRight->setEnabled(false);
            ui->actionFlip_Horizontal->setEnabled(false);
            ui->actionFlip_Vertical->setEnabled(false);
            ui->actionZoomIN->setEnabled(false);
            ui->actionZoom1_1->setEnabled(false);
            ui->actionZoomOut->setEnabled(false);
            ui->actionFitWindow->setEnabled(false);
            ui->actionPhotoInfo->setEnabled(false);
        }
    }
}

PhotoWindow::~PhotoWindow()
{
    delete ui;
}

void PhotoWindow::showEvent(QShowEvent *)
{
    //Photo Window Size & Post Setting
    {
        QRect ScreenSize = AdvancedPhoto::desktop()->screenGeometry();

        QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
        SettingsAP.beginGroup("PhotoWindowSizePos");

        if((SettingsAP.value("window_posx").toInt() != 0 && SettingsAP.value("window_posy").toInt() != 0) &&
           (SettingsAP.value("window_sizew").toInt() <= ScreenSize.width()+10 && SettingsAP.value("window_sizeh").toInt() <= ScreenSize.height()+10))
        {
            this->setGeometry(SettingsAP.value("window_posx").toInt(), SettingsAP.value("window_posy").toInt(),
                              SettingsAP.value("window_sizew").toInt(), SettingsAP.value("window_sizeh").toInt());
        }

        if( (QString(SettingsAP.value("window_max").toString()).isEmpty())
             || (QString(SettingsAP.value("window_max").toString())!="true"
             && QString(SettingsAP.value("window_max").toString())!="false"))
        {
            SettingsAP.setValue("window_max", "false");
        }

        if(SettingsAP.value("window_max").toBool() == true)
        {
            showMaximized();
        }

        if( (QString(SettingsAP.value("window_fuls").toString()).isEmpty())
             || (QString(SettingsAP.value("window_fuls").toString())!="true"
             && QString(SettingsAP.value("window_fuls").toString())!="false"))
        {
            SettingsAP.setValue("window_fuls", "false");
        }

        if(SettingsAP.value("window_fuls").toBool() == true)
        {
            showFullScreen();
        }

        SettingsAP.endGroup();
    }

    //MenuBar & ToolBar Height
    {
        mbh = this->menuBar()->height();

        if(ui->toolBar->height()<ui->toolBar->width())
        {
            tbh = ui->toolBar->height();
        }
        else
        {
            tbh = ui->toolBar->width();
        }
    }

    //Resize
    {
        if(pe == true)
        {
            ProcessingPhoto();
        }

        if(ui->toolBar->height() < ui->toolBar->width())
        {
            if(pe == false || iif == true)
            {
                ui->Photo->setGeometry (10, 10, ( this->geometry().width() - 20 ),
                                       ( this->geometry().height() - (mbh + tbh + ui->statusBar->height() + 20) ) );
            }
        }
        else
        {
            if(pe == false || iif == true)
            {
                ui->Photo->setGeometry (10, 10, ( this->geometry().width() - (20 + tbh) ),
                                       ( this->geometry().height() - (mbh + ui->statusBar->height() + 20) ) );
            }
        }
    }

    //Slideshow Timer
    {
        if(SlideshowSpeed <= 0 || SlideshowSpeed > 99)
        {
            SlideshowSpeed = 2;
        }

        Slideshow.setInterval(SlideshowSpeed*1000);
        Slideshow.connect(&Slideshow,SIGNAL(timeout()),this,SLOT(on_actionNext_Photo_triggered()));
    }

    //Screenshot Delay
    {
        if(ScreenshotDelay < 0 || ScreenshotDelay > 60)
        {
            ScreenshotDelay = 3;
        }
    }
}

void PhotoWindow::resizeEvent (QResizeEvent *)
{
    if(pe == true)
    {
        ProcessingPhoto();
    }

    if(ui->toolBar->height() < ui->toolBar->width())
    {
        if(pe == false || iif == true)
        {
            ui->Photo->setGeometry (10, 10, ( this->geometry().width() - 20 ),
                                   ( this->geometry().height() - (mbh + tbh + ui->statusBar->height() + 20) ) );
        }
    }
    else
    {
        if(pe == false || iif == true)
        {
            ui->Photo->setGeometry (10, 10, ( this->geometry().width() - (20 + tbh) ),
                                   ( this->geometry().height() - (mbh + ui->statusBar->height() + 20) ) );
        }
    }
}

void PhotoWindow::OpenArguments(QStringList Arguments)
{
    PhotoAddress = PhotoAddress + Arguments;

    if(oap == true && Arguments.count() <= 1)
    {
        QDir PhotoDir(QFileInfo(PhotoAddress[0]).path());
        QStringList PhotoFilter;
        PhotoFilter<<"*.png" << "*.jpg" << "*.bmp" << "*.tif" << "*.webp" << "*.gif"
                   << "*.jp2" << "*.dds" << "*.xpm" << "*.pnm" << "*.ppm" << "*.pgm"
                   << "*.wbmp" << "*.xbm" << "*.pbm" << "*.ico" << "*.icns";

        QFileInfoList Photos;

        Photos = PhotoDir.entryInfoList(PhotoFilter,QDir::Files);

        if(!Photos.isEmpty())
        {
            QString PhotoAddressBak=PhotoAddress[0];

            #if defined(Q_OS_WIN)
                PhotoAddressBak.replace("\\" , "/");
            #endif

            PhotoAddress.clear();

            for(int i=0; i<Photos.count(); i++)
            {
                PhotoAddress << Photos[i].absoluteFilePath();
            }

            ps=PhotoAddress.indexOf(PhotoAddressBak);
        }
    }

    pe=true;

    PhotoSelecter();
    ActionEnabler();
    ProcessingPhoto();
}

void PhotoWindow::on_actionToolBarMoved_triggered()
{
    if(pe == true)
    {
        ProcessingPhoto();
    }

    if(ui->toolBar->height() < ui->toolBar->width())
    {
        tbh = ui->toolBar->height();

        if(pe == false || iif == true)
        {
            ui->Photo->setGeometry (10, 10, ( this->geometry().width() - 20 ),
                                   ( this->geometry().height() - (mbh + tbh + ui->statusBar->height() + 20) ) );
        }
    }
    else
    {
        tbh = ui->toolBar->width();

        if(pe == false || iif == true)
        {
            ui->Photo->setGeometry (10, 10, ( this->geometry().width() - (20 + tbh) ),
                                   ( this->geometry().height() - (mbh + ui->statusBar->height() + 20) ) );
        }
    }
}

void PhotoWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void PhotoWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &purl, event->mimeData()->urls())
    {
        PhotoAddress << purl.toLocalFile();
    }

    if(!PhotoAddress.isEmpty())
    {
        pe=true;

        PhotoSelecter();
        ActionEnabler();
        ProcessingPhoto();
    }
}

void PhotoWindow::ActionEnabler()
{
    if(pe==true)
    {
        ui->Photo->setScaledContents(true);
        ui->actionSave->setEnabled(true);
        ui->actionSave_As->setEnabled(true);
        ui->actionClose_Photo->setEnabled(true);
        ui->actionPrint->setEnabled(true);
        ui->actionResize->setEnabled(true);
        ui->actionScreenshot->setEnabled(true);
        ui->actionZoomIN->setEnabled(true);
        ui->actionZoomOut->setEnabled(true);
        ui->actionRotateLeft->setEnabled(true);
        ui->actionRotateRight->setEnabled(true);
        ui->actionFlip_Horizontal->setEnabled(true);
        ui->actionFlip_Vertical->setEnabled(true);
        ui->actionPhotoInfo->setEnabled(true);

        if(PhotoAddress.count() > 1)
        {
            ui->actionSlideshow->setEnabled(true);
        }
        else
        {
            ui->actionSlideshow->setEnabled(false);
        }

        if(ps >= (PhotoAddress.count()-1) )
        {
            ui->actionNext_Photo->setEnabled(false);
        }
        else
        {
            ui->actionNext_Photo->setEnabled(true);
        }

        if(ps <= 0)
        {
            ui->actionPrevious_Photo->setEnabled(false);
        }
        else
        {
            ui->actionPrevious_Photo->setEnabled(true);
        }

        if(sls==true)
        {
            ui->actionRotateLeft->setEnabled(false);
            ui->actionRotateRight->setEnabled(false);
            ui->actionFlip_Horizontal->setEnabled(false);
            ui->actionFlip_Vertical->setEnabled(false);
            ui->actionResize->setEnabled(false);
            ui->actionSave->setEnabled(false);
            ui->actionSave_As->setEnabled(false);
            ui->actionPrint->setEnabled(false);
            ui->actionScreenshot->setEnabled(false);
        }
    }
    else
    {
        ui->Photo->setScaledContents(false);
        ui->Photo->setPixmap(QPixmap(":/Icons/Drop.png"));
        ui->statusBar->showMessage("");
        ui->actionZoomIN->setEnabled(false);
        ui->actionZoom1_1->setEnabled(false);
        ui->actionZoomOut->setEnabled(false);
        ui->actionFitWindow->setEnabled(false);
        ui->actionRotateLeft->setEnabled(false);
        ui->actionRotateRight->setEnabled(false);
        ui->actionFlip_Horizontal->setEnabled(false);
        ui->actionFlip_Vertical->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
        ui->actionResize->setEnabled(false);
        ui->actionPrint->setEnabled(false);
        ui->actionPhotoInfo->setEnabled(false);
    }

    if(iif==true)
    {
        ui->Photo->setScaledContents(false);
        ui->actionZoomIN->setEnabled(false);
        ui->actionZoom1_1->setEnabled(false);
        ui->actionZoomOut->setEnabled(false);
        ui->actionFitWindow->setEnabled(false);
        ui->actionRotateLeft->setEnabled(false);
        ui->actionRotateRight->setEnabled(false);
        ui->actionFlip_Horizontal->setEnabled(false);
        ui->actionFlip_Vertical->setEnabled(false);
        ui->actionResize->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
        ui->actionPrint->setEnabled(false);
        ui->actionPhotoInfo->setEnabled(false);

        if(ps >= (PhotoAddress.count()-1) )
        {
            ui->actionNext_Photo->setEnabled(false);
        }
        else
        {
            ui->actionNext_Photo->setEnabled(true);
        }

        if(PhotoAddress.count() > 1)
        {
            ui->actionSlideshow->setEnabled(true);
        }
        else
        {
            ui->actionSlideshow->setEnabled(false);
        }

        if(ps <= 0)
        {
            ui->actionPrevious_Photo->setEnabled(false);
        }
        else
        {
            ui->actionPrevious_Photo->setEnabled(true);
        }
        iif=false;
    }
}

void PhotoWindow::PhotoSelecter()
{
    ui->Photo->setPixmap(PhotoAddress[ps]);

    pi=PhotoAddress[ps];
    fi=PhotoAddress[ps];

    if (fi.size()<1024)
    {
        PSize = QString::number(fi.size()) + " Byte";
    }
    else if(fi.size()>=1024)
    {
        PSize = QString::number(fi.size()/1024) + " KB";
    }
}

void PhotoWindow::ProcessingPhoto()
{
    if(sph==true)
    {
        ui->Photo->setPixmap(PhotoSave);
        pi=(PhotoSave);

        if(ps != pst)
        {
            psb=ps;
            ps=pst;

            SavePhoto();

            if(SaveAnswer == QMessageBox::Save || SaveAnswer == QMessageBox::Discard)
            {
                ps=psb;

                ui->Photo->setPixmap(PhotoAddress[ps]);
                pi=(PhotoAddress[ps]);
            }
        }
    }

    if(!ui->Photo->pixmap()->isNull())
    {
        iif=false;

        if(ui->toolBar->height() < ui->toolBar->width())
        {
            ww = this->geometry().width()-20;
            wh = ( (this->geometry().height() ) - (mbh + tbh + ui->statusBar->height() + 20));
        }
        else
        {
            ww = this->geometry().width()- (20 + tbh);
            wh = ( (this->geometry().height() ) - (mbh + ui->statusBar->height() + 20));
        }

        if(kar==true)
        {
            pw=ui->Photo->pixmap()->width();
            ph=ui->Photo->pixmap()->height();

            ui->actionZoom1_1->setEnabled(true);

            zw=pw/100;
            zh=ph/100;

            pw2=pw;
            ph2=ph;

            //j
            {
                if(pw<=10000 && ph<=10000)
                {
                    j=10000;
                }

                if(pw<=1000 && ph<=1000)
                {
                    j=1000;
                }

                if(pw<=100 && ph<=100)
                {
                    j=100;
                }

                if(pw>10000 || ph>10000)
                {
                    j=100000;
                }
            }

            if(pw>ww||ph>wh)
            {
                for(int i=j; pw2>ww || ph2>wh; i--)
                {
                    pw2=((pw*i)/j);
                    ph2=((ph*i)/j);
                }
            }

            if(zoom == false)
            {
                ui->Photo->setGeometry( ( ( (ww - pw2) / 2) + 10), ( ( (wh - ph2) / 2) + 10), pw2, ph2);

                ui->actionFitWindow->setEnabled(false);

                if(pw2 >= ph2)
                {
                    zoomp = pw2/zw;
                }

                if(ph2 >= pw2)
                {
                    zoomp = ph2/zh;
                }

                ui->statusBar->showMessage("| " + QString::number(zoomp) + "%" + tr(" Zoom") + " | "
                                           + QFileInfo(PhotoAddress[ps]).fileName() + " | " +  QString::number(pi.width())
                                           + "x" + QString::number(pi.height()) + " | " + PSize + " | "
                                           + QString::number(ps+1) + tr(" of ") + QString::number(PhotoAddress.count()) + " |", 0);
            }
            else
            {
                ui->Photo->setGeometry( ( ( (ww - pwz) / 2) +10), ( ( (wh - phz) / 2) + 10), pwz, phz);

                ui->actionFitWindow->setEnabled(true);

                if(pwz >= phz)
                {
                    zoomp = pwz/zw;
                }

                if(phz >= pwz)
                {
                    zoomp = phz/zh;
                }

                ui->statusBar->showMessage("| " + QString::number(zoomp) + "%" + tr(" Zoom") + " | "
                                           + QFileInfo(PhotoAddress[ps]).fileName() + " | " +  QString::number(pi.width())
                                           + "x" + QString::number(pi.height()) + " | " + PSize + " | "
                                           + QString::number(ps+1) + tr(" of ") + QString::number(PhotoAddress.count()) + " |", 0);
            }
        }
        else
        {
            pw=ui->Photo->pixmap()->width();
            ph=ui->Photo->pixmap()->height();

            ui->actionZoom1_1->setEnabled(false);

            zw=pw/100;
            zh=ph/100;

            if(zoom == false)
            {
                ui->Photo->setGeometry(10, 10, ww, wh);

                ui->actionFitWindow->setEnabled(false);

                if(pw >= ph)
                {
                    zoomp = ww/zw;
                }

                if(ph >= pw)
                {
                    zoomp = wh/zh;
                }

                ui->statusBar->showMessage("| " + QString::number(zoomp) + "%" + tr(" Zoom") + " | "
                                           + QFileInfo(PhotoAddress[ps]).fileName() + " | " +  QString::number(pi.width())
                                           + "x" + QString::number(pi.height()) + " | " + PSize + " | "
                                           + QString::number(ps+1) + tr(" of ") + QString::number(PhotoAddress.count()) + " |", 0);
            }
            else
            {
                ui->Photo->setGeometry(( ( (ww - pwz) / 2) +10), ( ( (wh - phz) / 2) + 10), pwz, phz);

                ui->actionFitWindow->setEnabled(true);

                if(pwz >= phz)
                {
                    zoomp = pwz/zw;
                }

                if(phz >= pwz)
                {
                    zoomp = phz/zh;
                }

                ui->statusBar->showMessage("| " + QString::number(zoomp) + "%" + tr(" Zoom") + " | "
                                           + QFileInfo(PhotoAddress[ps]).fileName() + " | " +  QString::number(pi.width())
                                           + "x" + QString::number(pi.height()) + " | " + PSize + " | "
                                           + QString::number(ps+1) + tr(" of ") + QString::number(PhotoAddress.count()) + " |", 0);
            }
        }

        pst=ps;
    }
    else
    {
        iif=true;

        ui->statusBar->showMessage("| " + PhotoAddress[ps] + tr(" is Incorrect data !") + " | " + PSize + " | "
                                   + QString::number(ps+1) + tr(" of ") + QString::number(PhotoAddress.count()) + " |", 0);

        ui->Photo->setScaledContents(false);
        ui->Photo->setPixmap(QPixmap(":/Icons/Drop.png"));

        if(ui->toolBar->height() < ui->toolBar->width())
        {
            ui->Photo->setGeometry (10, 10, ( this->geometry().width() - 20 ),
                                    ( this->geometry().height() - (mbh + tbh + ui->statusBar->height() + 20) ) );
        }
        else
        {
            ui->Photo->setGeometry (10, 10, ( this->geometry().width() - (20 + tbh) ),
                                    ( this->geometry().height() - (mbh + ui->statusBar->height() + 20) ) );
        }

        //Clean
        {
            pw=0;
            ph=0;
            ww=0;
            wh=0;
            j=0;
            zw=0;
            zh=0;
            pwz=0;
            phz=0;
            pw2=0;
            ph2=0;
            zoom=false;
        }

        ActionEnabler();
    }
}

void PhotoWindow::SavePhoto()
{
    if(pe==true && sph==true && iif==false)
    {
        QFileInfo SaveFile = PhotoAddress[ps];

        QMessageBox SaveMsg(this);
        SaveMsg.setWindowTitle(tr("Save Changes"));
        SaveMsg.setText(tr("The Photo has been edited."));
        SaveMsg.setInformativeText(tr("Do you want to save your changes?"));
        SaveMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        SaveMsg.setDefaultButton(QMessageBox::Save);
        SaveMsg.setButtonText(QMessageBox::Save, tr("Save"));
        SaveMsg.setButtonText(QMessageBox::Discard, tr("Discard"));
        SaveMsg.setButtonText(QMessageBox::Cancel, tr("Cancel"));
        SaveAnswer = SaveMsg.exec();

        if(SaveAnswer == QMessageBox::Save)
        {
            if((SaveFile.suffix().toLower() == "png" || SaveFile.suffix().toLower() == "jpg"
                || SaveFile.suffix().toLower() == "jpeg" || SaveFile.suffix().toLower() == "bmp"
                || SaveFile.suffix().toLower() == "tif" || SaveFile.suffix().toLower() == "tiff"
                || SaveFile.suffix().toLower() == "webp" || SaveFile.suffix().toLower() == "jp2"
                || SaveFile.suffix().toLower() == "dds" || SaveFile.suffix().toLower() == "ppm"
                || SaveFile.suffix().toLower() == "xpm" || SaveFile.suffix().toLower() == "pgm"
                || SaveFile.suffix().toLower() == "xbm" || SaveFile.suffix().toLower() == "pbm") && ssh == false)
            {
                PhotoSave=PhotoSave.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(PhotoAddress[ps]).open(QIODevice::ReadWrite))
                {
                    PhotoSave.save(PhotoAddress[ps]);
                    sph=false;
                    ui->actionSave->setEnabled(false);
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();

                    SaveAnswer = QMessageBox::Cancel;
                    ActionEnabler();
                }
            }
            else
            {
                ui->actionSave->setEnabled(false);
                on_actionSave_As_triggered();
            }
        }
        else if (SaveAnswer == QMessageBox::Discard)
        {
            qDebug()<<"0";
            if(ssh==true)
            {
                qDebug()<<"1";
                Close_Photo();
                qDebug()<<"2";

                ActionEnabler();
                QFile::remove(ScreenshotFile);
                ssh=false;
            }

            sph=false;
            ui->actionSave->setEnabled(false);
        }
        else if (SaveAnswer == QMessageBox::Cancel)
        {
            ActionEnabler();
        }
    }
}

void PhotoWindow::Screenshot()
{
    ScreenshotTimer.stop();

    QScreen *Shot = QGuiApplication::primaryScreen();

    #if defined(Q_OS_WIN)
        ScreenshotFile = QString(QString(getenv("TEMP")) + "/APScreenshot" + QUuid::createUuid().toString() + ".png").replace("//", "/");
    #else
        if(!QString(getenv("TMPDIR")).isEmpty())
        {
            ScreenshotFile = QString(QString(getenv("TMPDIR")) + "/APScreenshot" + QUuid::createUuid().toString() + ".png").replace("//", "/");
        }
        else
        {
            ScreenshotFile = "/tmp/APScreenshot" + QUuid::createUuid().toString() + ".png";
        }
    #endif

    QPixmap SaveScreenshot = Shot->grabWindow(0);

    if(QFile(ScreenshotFile).open(QIODevice::ReadWrite))
    {
        SaveScreenshot.save(ScreenshotFile, "png");
    }
    else
    {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle(tr("Error"));
        msg.setText(tr("Can't Write File"));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setButtonText(QMessageBox::Ok, tr("OK"));
        msg.exec();
    }

    PhotoAddress << ScreenshotFile;

    if(!PhotoAddress.isEmpty())
    {
        //Clean
        {
            pw=0;
            ph=0;
            ww=0;
            wh=0;
            j=0;
            zw=0;
            zh=0;
            pwz=0;
            phz=0;
            pw2=0;
            ph2=0;
            zoom=false;
            ps=0;
            sph=false;
            ui->actionSave->setEnabled(false);
            if(sls==true)
            {
                Slideshow.stop();
                sls=false;

                ui->actionSlideshow->setIcon(QIcon(":/Icons/Slideshow Start.png"));
                ui->actionFlip_Horizontal->setEnabled(true);
                ui->actionFlip_Vertical->setEnabled(true);
                ui->actionResize->setEnabled(true);
                ui->actionRotateLeft->setEnabled(true);
                ui->actionRotateRight->setEnabled(true);
            }
        }

        PhotoSave=PhotoSave.fromImage(SaveScreenshot.toImage());

        ui->Photo->setPixmap(PhotoSave);

        ssh=true;
        pe=true;
        ps=PhotoAddress.count()-1;
        PhotoSelecter();
        ActionEnabler();
        ProcessingPhoto();
        sph=true;
    }

    if(sam == true)
    {
        Restore();
    }
}

void PhotoWindow::ScreenshotIcon()
{
    if (sam == true)
    {
        qDebug()<<IconTrayNum;
//        if (IconTrayNum == 1)
//        {
//            tray->setIcon(QIcon(":/Screenshot/Icons/Screenshot/tray1d.png"));
//            IconTrayNum--;
//        }
        if(IconTrayNum > 0)
        {
            tray->setIcon(QIcon(":/Screenshot/Icons/Screenshot/tray" + QString::number(IconTrayNum) + ".png"));
            IconTrayNum--;
        }
        else
        {
            IconTrayNum=0;
            ScreenshotTime.stop();
        }
    }
    else
    {
        if(IconTrayNum > 1)
        {
            ui->Photo->setPixmap(QPixmap(":/Screenshot/Icons/Screenshot/" + QString::number(IconTrayNum) + ".png"));
            IconTrayNum--;
        }
        else if (IconTrayNum == 1)
        {
            ui->Photo->setPixmap(QPixmap(":/Screenshot/Icons/Screenshot/1d.png"));
            IconTrayNum--;
        }
        else
        {
            ScreenshotTime.stop();
        }
    }
}

void PhotoWindow::Close_Photo()
{
    if(PhotoAddress.count() > 0)
    {
        PhotoAddress.removeAt(ps);

        qDebug()<<ps;

        if(ps > 0)
        {
            qDebug()<<"y";
            ps--;

            PhotoSelecter();
            ActionEnabler();
            ProcessingPhoto();
        }
        else if (ps == 0)
        {
            if (PhotoAddress.count() > 0)
            {
                PhotoSelecter();
                ActionEnabler();
                ProcessingPhoto();
            }
            else if(PhotoAddress.count() == 0)
            {
                pe=false;
                ActionEnabler();
            }
        }
    }
    else if (PhotoAddress.count() == 0)
    {
        pe=false;
        ActionEnabler();
    }
}

void PhotoWindow::Restore()
{
    tray->hide();
    show();
}

void PhotoWindow::closeEvent (QCloseEvent *event)
{
    if(sph==true)
    {
        SavePhoto();

        if (SaveAnswer == QMessageBox::Cancel)
        {
           event->ignore();
        }
    }

    QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());

    SettingsAP.beginGroup("PhotoWindowSizePos");

    if(!isMaximized() && !isFullScreen())
    {
        SettingsAP.setValue("window_posx", this->geometry().x() );
        SettingsAP.setValue("window_posy", this->geometry().y() );

        SettingsAP.setValue("window_sizew", this->geometry().width() );
        SettingsAP.setValue("window_sizeh", this->geometry().height() );
    }

    SettingsAP.setValue("window_max", isMaximized());
    SettingsAP.setValue("window_fuls", isFullScreen());

    SettingsAP.endGroup();
}

void PhotoWindow::on_actionOpen_triggered()
{
    QFileDialog OpenPhoto(this);
    OpenPhoto.setFileMode(QFileDialog::ExistingFiles);
    OpenPhoto.setNameFilter("All Supported Files (*.png ; *.jpg ; *.jpeg ; *.bmp ; *.tif ; *.tiff ; *.webp ;"
                               "*.gif ; *.jp2 ; *.dds ; *.xpm ; *.pnm ; *.ppm ; *.pgm ; *.wbmp ; *.xbm ; *.pbm ;"
                               "*.ico ; *.icns);; Photo (*.png ; *.jpg ; *.jpeg ; *.bmp ; *.tif ; *.tiff ; *.webp ;"
                               "*.gif ; *.jp2 ; *.dds ; *.xpm ; *.pnm ; *.ppm ; *.pgm ; *.wbmp ; *.xbm ; *.pbm);;"
                               "Icon (*.ico ; *.icns);; All Files(*)");

    OpenPhoto.setWindowTitle(tr("Open Photo"));

    //Load Directory
    {
        QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
        SettingsAP.beginGroup("Directory");

        if (!SettingsAP.value("Directory").toString().isEmpty())
        {
            OpenPhoto.setDirectory(SettingsAP.value("Directory").toString());
        }
        else
        {
            #if defined(Q_OS_WIN)
            if (!QString(getenv("HOMEPATH")).contains(":"))
            {
                OpenPhoto.setDirectory("C:" + QString(getenv("HOMEPATH")));
            }
            else
            {
                OpenPhoto.setDirectory(getenv("HOMEPATH"));
            }
            #else
            OpenPhoto.setDirectory(getenv("HOME"));
            #endif
        }

        SettingsAP.endGroup();
    }

    if (OpenPhoto.exec())
    {
        PhotoAddress = OpenPhoto.selectedFiles();

        //Seve Directory
        {
            QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
            SettingsAP.beginGroup("Directory");
            SettingsAP.setValue("Directory", OpenPhoto.directory().path() );
            SettingsAP.endGroup();
        }

        if(!PhotoAddress.isEmpty())
        {
            //Clean
            {
                pw=0;
                ph=0;
                ww=0;
                wh=0;
                j=0;
                zw=0;
                zh=0;
                pwz=0;
                phz=0;
                pw2=0;
                ph2=0;
                zoom=false;
                ps=0;
                sph=false;
                ui->actionSave->setEnabled(false);
                if(sls==true)
                {
                    Slideshow.stop();
                    sls=false;

                    ui->actionSlideshow->setIcon(QIcon(":/Icons/Slideshow Start.png"));
                    ui->actionFlip_Horizontal->setEnabled(true);
                    ui->actionFlip_Vertical->setEnabled(true);
                    ui->actionResize->setEnabled(true);
                    ui->actionRotateLeft->setEnabled(true);
                    ui->actionRotateRight->setEnabled(true);
                }
            }

            pe=true;

            PhotoSelecter();
            ActionEnabler();
            ProcessingPhoto();
        }
    }
}

void PhotoWindow::on_actionSave_triggered()
{
    if(pe==true && iif==false)
    {
        QFileInfo SaveFile = PhotoAddress[ps];

        if((SaveFile.suffix().toLower() == "png" || SaveFile.suffix().toLower() == "jpg"
         || SaveFile.suffix().toLower() == "jpeg" || SaveFile.suffix().toLower() == "bmp"
         || SaveFile.suffix().toLower() == "tif" || SaveFile.suffix().toLower() == "tiff"
         || SaveFile.suffix().toLower() == "webp" || SaveFile.suffix().toLower() == "jp2"
         || SaveFile.suffix().toLower() == "dds" || SaveFile.suffix().toLower() == "ppm"
         || SaveFile.suffix().toLower() == "xpm" || SaveFile.suffix().toLower() == "pgm"
         || SaveFile.suffix().toLower() == "xbm" || SaveFile.suffix().toLower() == "pbm") && ssh == false)
        {
            PhotoSave=PhotoSave.fromImage(ui->Photo->pixmap()->toImage());

            if(QFile(PhotoAddress[ps]).open(QIODevice::ReadWrite))
            {
                PhotoSave.save(PhotoAddress[ps]);

                sph=false;
                ui->actionSave->setEnabled(false);
            }
            else
            {
                QMessageBox msg(this);
                msg.setIcon(QMessageBox::Critical);
                msg.setWindowTitle(tr("Error"));
                msg.setText(tr("Can't Write File"));
                msg.setStandardButtons(QMessageBox::Ok);
                msg.setButtonText(QMessageBox::Ok, tr("OK"));
                msg.exec();
            }
        }
        else
        {
            ui->actionSave->setEnabled(false);
            on_actionSave_As_triggered();
        }
    }
}

void PhotoWindow::on_actionSave_As_triggered()
{
    if(pe==true && iif==false)
    {
        QFileInfo PhotoName = PhotoAddress[ps];
        QString Directory;

        //Load Directory
        {
            QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
            SettingsAP.beginGroup("Directory");

            if (!SettingsAP.value("Directory").toString().isEmpty())
            {
                Directory = SettingsAP.value("Directory").toString();
            }
            else
            {
                #if defined(Q_OS_WIN)
                if (!QString(getenv("HOMEPATH")).contains(":"))
                {
                    Directory = "C:" + QString(getenv("HOMEPATH"));
                }
                else
                {
                    Directory = getenv("HOMEPATH");
                }
                #else
                Directory = getenv("HOME");
                #endif
            }

            SettingsAP.endGroup();
        }

        QString SavePhotoFilter;
        QString SaveAddress = QFileDialog::getSaveFileName(this, tr("Save As Photo"),
                                                           Directory+"/"+PhotoName.baseName(),"Portable Network Graphics (*.png) ;;"
                                                                                        "JPEG Image (*.jpg) ;; BMP file format (*.bmp) ;;"
                                                                                        "Tagged Image File Format (*.tiff) ;; WebP (*.webp) ;;"
                                                                                        "JPEG 2000 (*.jp2) ;; DirectDraw Surface (*.dds) ;;"
                                                                                        "Portable Pixmap (*.ppm) ;; X11 Pixmap (*.xpm) ;;"
                                                                                        "Pgm (*.pgm) ;; X11 Bitmap (*.xbm) ;;"
                                                                                        "Netpbm format (*.pbm)", &SavePhotoFilter);

        if(!SaveAddress.isEmpty())
        {
            QFileInfo SaveFile = SaveAddress;

            //Seve Directory
            {
                QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
                SettingsAP.beginGroup("Directory");
                SettingsAP.setValue("Directory", SaveFile.path() );
                SettingsAP.endGroup();
            }

            if(SavePhotoFilter == "Portable Network Graphics (*.png)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".png";
                }

                QPixmap SavePNG = SavePNG.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SavePNG.save(SaveAddress,"png");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "JPEG Image (*.jpg)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".jpg";
                }

                QPixmap SaveJPG = SaveJPG.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveJPG.save(SaveAddress,"jpg");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "BMP file format (*.bmp)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".bmp";
                }

                QPixmap SaveBMP = SaveBMP.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveBMP.save(SaveAddress,"bmp");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "Tagged Image File Format (*.tiff)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".tiff";
                }

                QPixmap SaveTIF = SaveTIF.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveTIF.save(SaveAddress,"tif");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "WebP (*.webp)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".webp";
                }

                QPixmap SaveWEBP = SaveWEBP.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveWEBP.save(SaveAddress,"webp");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "JPEG 2000 (*.jp2)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".jp2";
                }

                QPixmap SaveJP2 = SaveJP2.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveJP2.save(SaveAddress,"jp2");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "DirectDraw Surface (*.dds)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".dds";
                }

                QPixmap SaveDDS = SaveDDS.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveDDS.save(SaveAddress,"dds");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "Portable Pixmap (*.ppm)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".ppm";
                }

                QPixmap SavePPM = SavePPM.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SavePPM.save(SaveAddress,"ppm");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "X11 Pixmap (*.xpm)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".xpm";
                }

                QPixmap SaveXPM = SaveXPM.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveXPM.save(SaveAddress,"xpm");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "Pgm (*.pgm)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".pgm";
                }

                QPixmap SavePGM = SavePGM.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SavePGM.save(SaveAddress,"pgm");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "X11 Bitmap (*.xbm)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".xbm";
                }

                QPixmap SaveXBM = SaveXBM.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SaveXBM.save(SaveAddress,"xbm");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }

            else if(SavePhotoFilter == "Netpbm format (*.pbm)")
            {
                if(SaveFile.suffix().isEmpty())
                {
                    SaveAddress=SaveAddress+".pbm";
                }

                QPixmap SavePBM = SavePBM.fromImage(ui->Photo->pixmap()->toImage());

                if(QFile(SaveAddress).open(QIODevice::ReadWrite))
                {
                    SavePBM.save(SaveAddress,"pbm");

                    sph=false;
                    PhotoAddress[ps]=SaveAddress;
                    PhotoSelecter();
                    ProcessingPhoto();
                }
                else
                {
                    QMessageBox msg(this);
                    msg.setIcon(QMessageBox::Critical);
                    msg.setWindowTitle(tr("Error"));
                    msg.setText(tr("Can't Write File"));
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setButtonText(QMessageBox::Ok, tr("OK"));
                    msg.exec();
                }
            }
        }
    }

    if(ssh == true)
    {
        ssh = false;
        QFile::remove(ScreenshotFile);
    }
}

void PhotoWindow::on_actionClose_Photo_triggered()
{
    if(pe == true)
    {
        if(sph==false)
        {
            Close_Photo();
        }
        else
        {
            SavePhoto();

            if(SaveAnswer == QMessageBox::Save || SaveAnswer == QMessageBox::Discard)
            {
                ActionEnabler();
                Close_Photo();
            }
            else
            {
                ActionEnabler();
            }
        }
    }
}

void PhotoWindow::on_actionOption_triggered()
{
    bool kart=kar;
    int SlideshowSpeedt=SlideshowSpeed;

    QDialog *OD = new option(this);
    OD->exec();

    if(pe==true && (kart != kar || SlideshowSpeedt != SlideshowSpeed))
    {
        //Clean
        {
            pw=0;
            ph=0;
            ww=0;
            wh=0;
            j=0;
            zw=0;
            zh=0;
            pwz=0;
            phz=0;
            pw2=0;
            ph2=0;
            zoom=false;
        }

        if(kar==true)
        {
            ui->actionZoom1_1->setEnabled(true);
        }

        if(kar==false)
        {
            ui->actionZoom1_1->setEnabled(false);
        }

        Slideshow.setInterval(SlideshowSpeed*1000);

        ProcessingPhoto();
    }
    ui->retranslateUi(this);
}

void PhotoWindow::on_actionPrint_triggered()
{
    QPrinter PhotoPrint;

    QPrintDialog *PhotoPrintDialog = new QPrintDialog(&PhotoPrint,0);

    if(PhotoPrintDialog->exec() == QDialog::Accepted)
    {
        QImage Photo(ui->Photo->pixmap()->toImage());
        QPainter painter(&PhotoPrint);
        painter.drawImage(QPoint(0,0),Photo);
        painter.end();
    }
}

void PhotoWindow::on_actionQuit_triggered()
{
    close();
}

void PhotoWindow::on_actionScreenshot_triggered()
{
    if(ssh==false)
    {
        if (sam == true)
        {
            QAction *RestoreAction = new QAction(QIcon(""), "Restore", this);
            connect(RestoreAction, SIGNAL(triggered()), this, SLOT(Restore()));

            QMenu *TrayMenu = new QMenu(this);
            TrayMenu->addAction(RestoreAction);

            tray = new QSystemTrayIcon(this);
            tray->setContextMenu(TrayMenu);
            tray->show();

            this->hide();

            if(ScreenshotDelay > 0)
            {
                IconTrayNum=ScreenshotDelay;
                ScreenshotIcon();
                ScreenshotTime.setInterval(1000);
                ScreenshotTime.connect(&ScreenshotTime,SIGNAL(timeout()),this,SLOT(ScreenshotIcon()));
                ScreenshotTime.start();
            }
            else
            {
                tray->setIcon(QIcon(":/Icons/Screenshot.png"));
            }
        }
        else
        {
            if(ScreenshotDelay > 0)
            {
                IconTrayNum=ScreenshotDelay;
                ScreenshotIcon();
                ScreenshotTime.setInterval(1000);
                ScreenshotTime.connect(&ScreenshotTime,SIGNAL(timeout()),this,SLOT(ScreenshotIcon()));
                ScreenshotTime.start();
            }
            else
            {
                ui->Photo->setPixmap(QPixmap(":/Icons/Screenshot.png"));
            }
        }

        if(ScreenshotDelay > 0)
        {
            ScreenshotTimer.setInterval(ScreenshotDelay*1000);
            ScreenshotTimer.connect(&ScreenshotTimer,SIGNAL(timeout()),this,SLOT(Screenshot()));
            ScreenshotTimer.start();
        }
        else
        {
            Screenshot();
        }
    }
    else
    {
        SavePhoto();

        if(SaveAnswer == QMessageBox::Save || SaveAnswer == QMessageBox::Discard)
        {
            ActionEnabler();
            ScreenshotTimer.stop();
            on_actionScreenshot_triggered();
        }
        else
        {
            ActionEnabler();
        }
    }
}

void PhotoWindow::on_actionHome_Page_triggered()
{
    QDesktopServices::openUrl(QUrl(AdvancedPhoto::organizationDomain()));
}

void PhotoWindow::on_actionAbout_triggered()
{
    QDialog *AD = new about(this);
    AD->exec();
}

void PhotoWindow::on_actionResize_triggered()
{
    if(pe==true)
    {
        QDialog *RPD = new resizephoto(this);
        RPD->exec();

        if(resz==true)
        {
            QImage Resize(ui->Photo->pixmap()->toImage());

            if(rd==90 || rd==270 || rd==-90 || rd==-270)
            {
                if(rekar==true)
                {
                    PhotoSave=PhotoSave.fromImage(Resize.scaled(RSHeight,RSWidth,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                else
                {
                    PhotoSave=PhotoSave.fromImage(Resize.scaled(RSHeight,RSWidth,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                }
            }
            else
            {
                if(rekar==true)
                {
                    PhotoSave=PhotoSave.fromImage(Resize.scaled(RSWidth,RSHeight,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                else
                {
                    PhotoSave=PhotoSave.fromImage(Resize.scaled(RSWidth,RSHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                }
            }

            resz=false;

            RSWidth=0;
            RSWidth=0;

            sph=true;
            ui->actionSave->setEnabled(true);
            ProcessingPhoto();
        }
    }
}

void PhotoWindow::on_actionRotateLeft_triggered()
{
    if(pe==true)
    {
        rd=rd-90;
        if(rd==-360)
        {
            rd=0;
        }

        PhotoSave=PhotoSave.fromImage(ui->Photo->pixmap()->toImage());
        QTransform Rotate;
        Rotate = Rotate.rotate(-90);

        PhotoSave=(PhotoSave.transformed(Rotate));

        ui->Photo->setPixmap(PhotoSave);

        sph=true;
        zoom=false;
        ui->actionSave->setEnabled(true);
        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionRotateRight_triggered()
{
    if(pe==true)
    {
        rd=rd+90;
        if(rd==360)
        {
            rd=0;
        }

        PhotoSave=PhotoSave.fromImage(ui->Photo->pixmap()->toImage());
        QTransform Rotate;
        Rotate = Rotate.rotate(90);

        PhotoSave=(PhotoSave.transformed(Rotate));

        ui->Photo->setPixmap(PhotoSave);

        sph=true;
        zoom=false;
        ui->actionSave->setEnabled(true);
        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionFlip_Horizontal_triggered()
{
    PhotoSave=PhotoSave.fromImage(ui->Photo->pixmap()->toImage());

    QImage Flip=PhotoSave.toImage();

    PhotoSave=PhotoSave.fromImage(Flip.mirrored(true,false));

    ui->Photo->setPixmap(PhotoSave);

    sph=true;
    ui->actionSave->setEnabled(true);
    ProcessingPhoto();
}

void PhotoWindow::on_actionFlip_Vertical_triggered()
{
    PhotoSave=PhotoSave.fromImage(ui->Photo->pixmap()->toImage());

    QImage Flip=PhotoSave.toImage();

    PhotoSave=PhotoSave.fromImage(Flip.mirrored(false,true));

    ui->Photo->setPixmap(PhotoSave);

    sph=true;
    ui->actionSave->setEnabled(true);
    ProcessingPhoto();
}

void PhotoWindow::on_actionZoomIN_triggered()
{
    if(pe==true)
    {
        zoom=true;

        pwz=ui->Photo->geometry().width() + zw;
        phz=ui->Photo->geometry().height() + zh;

        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionZoom1_1_triggered()
{
    if(pe==true && kar==true)
    {
        zoom=true;

        ui->actionFitWindow->setEnabled(true);

        pwz=pw;
        phz=ph;

        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionZoomOut_triggered()
{
    if(pe==true)
    {
        ui->actionFitWindow->setEnabled(true);

        zoom=true;

        if(ui->Photo->geometry().width() > zw && ui->Photo->geometry().height() > zh)
        {
            pwz=ui->Photo->geometry().width() - zw;
            phz=ui->Photo->geometry().height() - zh;
        }

        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionFitWindow_triggered()
{
    if(pe==true && zoom==true)
    {
        zoom = false;

        ui->actionFitWindow->setEnabled(false);

        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionPrevious_Photo_triggered()
{
    if(pe==true && PhotoAddress.count() > 1 && ps > 0)
    {
        ps--;

        zoom=false;

        PhotoSelecter();
        ActionEnabler();
        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionSlideshow_triggered()
{
    if(sls==false && pe==true && PhotoAddress.count() > 1)
    {
        Slideshow.start();
        sls=true;

        ui->actionSlideshow->setIcon(QIcon(":/Icons/Slideshow Stop.png"));
        ui->actionSlideshow->setToolTip("Stop Slideshow");

        ActionEnabler();

        if(sgf==true)
        {
            if(!isFullScreen())
            {
                if(isMaximized())
                {
                    wasMax=true;
                }
                else
                {
                    wasMax=false;
                }

                showFullScreen();

                ui->actionFullscreen->setIcon(QIcon(":/Icons/Normal Screen.png"));
                ui->actionFullscreen->setToolTip("Exit Full Screen");
            }
        }
    }
    else if (sls==true)
    {
        Slideshow.stop();
        sls=false;

        ui->actionSlideshow->setIcon(QIcon(":/Icons/Slideshow Start.png"));
        ui->actionSlideshow->setToolTip(tr("Start Slideshow"));

        ActionEnabler();

        if(sgf==true)
        {
            if(isFullScreen())
            {
                if(wasMax==true)
                {
                    showMaximized();
                }
                else if (wasMax==false)
                {
                    showNormal();
                }

                ui->actionFullscreen->setIcon(QIcon(":/Icons/Full Screen.png"));
                ui->actionFullscreen->setToolTip(tr("Full Screen"));
            }
        }
    }
}

void PhotoWindow::on_actionNext_Photo_triggered()
{
    if(sls == true && ps == (PhotoAddress.count()-1))
    {
        ps=-1;
    }

    if(pe==true && PhotoAddress.count() > 1 && ps <= (PhotoAddress.count()-1) )
    {
        ps++;

        zoom=false;

        PhotoSelecter();
        ActionEnabler();
        ProcessingPhoto();
    }
}

void PhotoWindow::on_actionPhotoInfo_triggered()
{
    if(pe == true)
    {
        QDialog *PID = new photoinfo(this);
        PID->exec();
    }
}

void PhotoWindow::on_actionFullscreen_triggered()
{
    if(!isFullScreen())
    {
        if(isMaximized())
        {
            wasMax=true;
        }
        else
        {
            wasMax=false;
        }

        showFullScreen();

        ui->actionFullscreen->setIcon(QIcon(":/Icons/Normal Screen.png"));
        ui->actionFullscreen->setToolTip(tr("Exit Full Screen"));
    }
    else
    {
        if(wasMax==true)
        {
            showMaximized();
        }
        else if (wasMax==false)
        {
            showNormal();
        }

        ui->actionFullscreen->setIcon(QIcon(":/Icons/Full Screen.png"));
        ui->actionFullscreen->setToolTip(tr("Full Screen"));
    }
}

#include "photoinfo.h"
#include "ui_photoinfo.h"
#include "advancedphoto.h"

#include <QFileInfo>
#include <QDateTime>

#include <QDebug>

photoinfo::photoinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::photoinfo)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

photoinfo::~photoinfo()
{
    delete ui;
}

void photoinfo::showEvent(QShowEvent *)
{
    extern QStringList PhotoAddress;
    extern int ps;

    ui->NamePI->setText(QFileInfo(PhotoAddress[ps]).fileName());
    ui->DirectoryPI->setText(QFileInfo(PhotoAddress[ps]).path());

    if (QFileInfo(PhotoAddress[ps]).size()<1024)
    {
        ui->SizePI->setText(QString::number(QFileInfo(PhotoAddress[ps]).size()) + " Byte");
    }
    else if(QFileInfo(PhotoAddress[ps]).size()>=1024)
    {
        ui->SizePI->setText(QString::number(QFileInfo(PhotoAddress[ps]).size()/1024) + " KB");
    }

    if(QFileInfo(PhotoAddress[ps]).suffix().toLower().toLower() == "png")
    {
        ui->TypePI->setText("Portable Network Graphics");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "jpg"|| QFileInfo(PhotoAddress[ps]).suffix().toLower() == "jpeg")
    {
        ui->TypePI->setText("JPEG Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "bmp")
    {
        ui->TypePI->setText("BMP file format");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "tif" || QFileInfo(PhotoAddress[ps]).suffix().toLower() == "tiff")
    {
        ui->TypePI->setText("Tagged Image File Format");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "webp")
    {
        ui->TypePI->setText("WebP");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "gif")
    {
        ui->TypePI->setText("GIF Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "jp2")
    {
        ui->TypePI->setText("JPEG 2000");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "dds")
    {
        ui->TypePI->setText("DirectDraw Surface");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "ppm")
    {
        ui->TypePI->setText("Portable Pixmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "xpm")
    {
        ui->TypePI->setText("X11 Pixmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "pnm")
    {
        ui->TypePI->setText("PNM Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "ppm")
    {
        ui->TypePI->setText("PNM Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "pgm")
    {
        ui->TypePI->setText("Pgm Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "wbmp")
    {
        ui->TypePI->setText("Wireless Bitmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "xbm")
    {
        ui->TypePI->setText("X11 Bitmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "ico")
    {
        ui->TypePI->setText("Windows Icon format");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix().toLower() == "icns")
    {
        ui->TypePI->setText("Apple Icon Image format");
    }
    else
    {
        if(!QFileInfo(PhotoAddress[ps]).suffix().isEmpty())
        {
            ui->TypePI->setText(QFileInfo(PhotoAddress[ps]).suffix()+" File");
        }
        else
        {
            ui->TypePI->setText("Unknown File");
        }
    }

    ui->WidthPI->setNum(QPixmap(PhotoAddress[ps]).width());
    ui->HeightPI->setNum(QPixmap(PhotoAddress[ps]).height());
    ui->DataCreatedPI->setText(QFileInfo(PhotoAddress[ps]).created().date().toString());

    if(AdvancedPhoto::layoutDirection() == Qt::LeftToRight)
    {
        ui->NamePI->setAlignment(Qt::AlignLeft);
        ui->DirectoryPI->setAlignment(Qt::AlignLeft);
        ui->SizePI->setAlignment(Qt::AlignLeft);
        ui->TypePI->setAlignment(Qt::AlignLeft);
        ui->WidthPI->setAlignment(Qt::AlignLeft);
        ui->HeightPI->setAlignment(Qt::AlignLeft);
    }
    else
    {
        ui->NamePI->setAlignment(Qt::AlignRight);
        ui->DirectoryPI->setAlignment(Qt::AlignRight);
        ui->SizePI->setAlignment(Qt::AlignRight);
        ui->TypePI->setAlignment(Qt::AlignRight);
        ui->WidthPI->setAlignment(Qt::AlignRight);
        ui->HeightPI->setAlignment(Qt::AlignRight);
    }
}

void photoinfo::on_OkButton_clicked()
{
    close();
}

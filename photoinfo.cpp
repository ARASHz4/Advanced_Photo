#include "photoinfo.h"
#include "ui_photoinfo.h"

#include <QFileInfo>
#include <QDateTime>

extern QStringList PhotoAddress;
extern int ps;

photoinfo::photoinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::photoinfo)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

photoinfo::~photoinfo()
{
    delete ui;
}

void photoinfo::showEvent(QShowEvent *)
{
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

    if(QFileInfo(PhotoAddress[ps]).suffix() == "png" || QFileInfo(PhotoAddress[ps]).suffix() == "PNG")
    {
        ui->TypePI->setText("Portable Network Graphics");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "jpg" || QFileInfo(PhotoAddress[ps]).suffix() == "JPG" ||
            QFileInfo(PhotoAddress[ps]).suffix() == "jpeg" || QFileInfo(PhotoAddress[ps]).suffix() == "JPEG")
    {
        ui->TypePI->setText("JPEG Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "bmp" || QFileInfo(PhotoAddress[ps]).suffix() == "BMP")
    {
        ui->TypePI->setText("BMP file format");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "tif" || QFileInfo(PhotoAddress[ps]).suffix() == "tiff" ||
            QFileInfo(PhotoAddress[ps]).suffix() == "TIF" || QFileInfo(PhotoAddress[ps]).suffix() == "TIFF")
    {
        ui->TypePI->setText("Tagged Image File Format");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "webp" || QFileInfo(PhotoAddress[ps]).suffix() == "WEBP")
    {
        ui->TypePI->setText("WebP");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "gif" || QFileInfo(PhotoAddress[ps]).suffix() == "GIF")
    {
        ui->TypePI->setText("GIF Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "jp2" || QFileInfo(PhotoAddress[ps]).suffix() == "JP2")
    {
        ui->TypePI->setText("JPEG 2000");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "dds" || QFileInfo(PhotoAddress[ps]).suffix() == "DDS")
    {
        ui->TypePI->setText("DirectDraw Surface");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "ppm" || QFileInfo(PhotoAddress[ps]).suffix() == "PPM")
    {
        ui->TypePI->setText("Portable Pixmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "xpm" || QFileInfo(PhotoAddress[ps]).suffix() == "XPM")
    {
        ui->TypePI->setText("X11 Pixmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "pnm" || QFileInfo(PhotoAddress[ps]).suffix() == "PNM")
    {
        ui->TypePI->setText("PNM Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "ppm" || QFileInfo(PhotoAddress[ps]).suffix() == "PPM")
    {
        ui->TypePI->setText("PNM Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "pgm" || QFileInfo(PhotoAddress[ps]).suffix() == "PGM")
    {
        ui->TypePI->setText("Pgm Image");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "wbmp" || QFileInfo(PhotoAddress[ps]).suffix() == "WBMP")
    {
        ui->TypePI->setText("Wireless Bitmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "xbm" || QFileInfo(PhotoAddress[ps]).suffix() == "XBM")
    {
        ui->TypePI->setText("X11 Bitmap");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "ico" || QFileInfo(PhotoAddress[ps]).suffix() == "ICO")
    {
        ui->TypePI->setText("Windows Icon format");
    }
    else if(QFileInfo(PhotoAddress[ps]).suffix() == "icns" || QFileInfo(PhotoAddress[ps]).suffix() == "ICNS")
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
}

void photoinfo::on_OkButton_clicked()
{
    close();
}

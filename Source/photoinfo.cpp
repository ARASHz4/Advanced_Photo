#include "photoinfo.h"
#include "ui_photoinfo.h"
#include "advancedphoto.h"
#include "photowindow.h"

PhotoInfo::PhotoInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhotoInfo)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Start();
}

PhotoInfo::~PhotoInfo()
{
    delete ui;
}

void PhotoInfo::Start()
{
    QFileIconProvider iconf;

    ui->IconLabel->setPixmap(iconf.icon(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()])).pixmap(QSize(16, 16)));
    ui->NamePI->setText(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).fileName());
    ui->DirectoryPI->setText(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).path());

    if (QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).size()<1024)
    {
        ui->SizePI->setText(QString::number(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).size()) + " Byte");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).size()>=1024)
    {
        ui->SizePI->setText(QString::number(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).size()/1024) + " KB");
    }

    if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower().toLower() == "png")
    {
        ui->TypePI->setText("Portable Network Graphics");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "jpg"
            || QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "jpeg")
    {
        ui->TypePI->setText("JPEG Image");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "bmp")
    {
        ui->TypePI->setText("BMP file format");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "tif"
            || QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "tiff")
    {
        ui->TypePI->setText("Tagged Image File Format");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "webp")
    {
        ui->TypePI->setText("WebP");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "svg"
            || QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "svgz")
    {
        ui->TypePI->setText("Scalable Vector Graphics");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "gif")
    {
        ui->TypePI->setText("GIF Image");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "dds")
    {
        ui->TypePI->setText("DirectDraw Surface");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "ppm")
    {
        ui->TypePI->setText("Portable Pixmap");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "xpm")
    {
        ui->TypePI->setText("X11 Pixmap");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "pnm")
    {
        ui->TypePI->setText("PNM Image");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "ppm")
    {
        ui->TypePI->setText("PNM Image");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "pgm")
    {
        ui->TypePI->setText("Pgm Image");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "wbmp")
    {
        ui->TypePI->setText("Wireless Bitmap");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "xbm")
    {
        ui->TypePI->setText("X11 Bitmap");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "ico")
    {
        ui->TypePI->setText("Windows Icon format");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "icns")
    {
        ui->TypePI->setText("Apple Icon Image format");
    }
    else if(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().toLower() == "cur")
    {
        ui->TypePI->setText("Cursors file");
    }
    else
    {
        if(!QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix().isEmpty())
        {
            ui->TypePI->setText(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).suffix()+" File");
        }
        else
        {
            ui->TypePI->setText("Unknown File");
        }
    }

    ui->WidthPI->setNum(QPixmap(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).width());
    ui->HeightPI->setNum(QPixmap(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).height());
    ui->DataCreatedPI->setText(QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).created().date().toString());

    if (AdvancedPhoto::layoutDirection() == Qt::RightToLeft)
    {
        QString nm = QFileInfo(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]).fileName().mid(0,1);
        if(nm.contains(QRegExp("([0-9]|[A-z]){1}")))
        {
            ui->NamePI->setAlignment(Qt::AlignRight);
        }
        ui->DirectoryPI->setAlignment(Qt::AlignRight);
        ui->SizePI->setAlignment(Qt::AlignRight);
        ui->TypePI->setAlignment(Qt::AlignRight);
        ui->WidthPI->setAlignment(Qt::AlignRight);
        ui->HeightPI->setAlignment(Qt::AlignRight);

        QString dm = ui->DataCreatedPI->text().mid(0,1);
        if(dm.contains(QRegExp("([0-9]|[A-z]){1}")))
        {
            ui->DataCreatedPI->setAlignment(Qt::AlignRight);
        }
    }
}

void PhotoInfo::on_OkButton_clicked()
{
    close();
}

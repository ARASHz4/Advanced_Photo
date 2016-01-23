#include "resizephoto.h"
#include "ui_resizephoto.h"
#include "photowindow.h"

#include <QStringList>
#include <QPixmap>

int ResizePhoto::rsWidth=0, ResizePhoto::rsHeight=0;
bool ResizePhoto::rekar=false, ResizePhoto::resz=false;

ResizePhoto::ResizePhoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizePhoto)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Start();
}

ResizePhoto::~ResizePhoto()
{
    delete ui;
}

void ResizePhoto::setRsWidth(int value)
{
    rsWidth = value;
}

int ResizePhoto::RsWidth()
{
    return rsWidth;
}

void ResizePhoto::setRsHeight(int value)
{
    rsHeight = value;
}

int ResizePhoto::RsHeight()
{
    return rsHeight;
}

void ResizePhoto::setRekar(bool value)
{
    rekar = value;
}

bool ResizePhoto::Rekar()
{
    return rekar;
}

void ResizePhoto::setResz(bool value)
{
    resz = value;
}

bool ResizePhoto::Resz()
{
    return resz;
}

void ResizePhoto::Start()
{
    rsWidth=0;
    rsHeight=0;
    w=0;
    h=0;
    tw=0;
    th=0;
    rekar=false;
    resz=false;
    wc=true;
    hc=true;

    //Photo Size
    {
        QPixmap PSize(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]);

        wc=false;
        hc=false;
        ui->Width->setValue(PSize.width());
        ui->Height->setValue(PSize.height());
        wc=true;
        hc=true;

        w=ui->Width->value();
        h=ui->Height->value();
        wvt=ui->Width->value();
        hvt=ui->Height->value();

        OK.connect(&OK, SIGNAL(clicked()), this, SLOT(OKButton()));
        Cancel.connect(&Cancel, SIGNAL(clicked()), this, SLOT(CancelButton()));
        OK.setText(tr("OK"));
        Cancel.setText(tr("Cancel"));
        OK.setDefault(true);

        ui->ResizeButtonBox->addButton(&OK, QDialogButtonBox::AcceptRole);
        ui->ResizeButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);
    }
}

void ResizePhoto::on_Width_valueChanged()
{
    if(ui->KeepAspectRatio->isChecked()==true && wc==true)
    {
        QImage Resize(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]);

        if(ui->Width->value()>wvt)
        {
            tw = tw+1;

            if(w<=h)
            {
                pres=pres.fromImage(Resize.scaled(w+tw ,h+tw ,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
            }

            if(h<w)
            {
                pres=pres.fromImage(Resize.scaled(h+tw ,w+tw ,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }

            this->SetValue();
        }

        if(ui->Width->value()<wvt)
        {
            tw=tw-1;

            if(w<=h)
            {
                pres=pres.fromImage(Resize.scaled(w+tw ,h+tw ,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
            }

            if(h<w)
            {
                pres=pres.fromImage(Resize.scaled(h+tw ,w+tw ,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }

            this->SetValue();
        }

        wvt=ui->Width->value();
    }
}

void ResizePhoto::on_Height_valueChanged()
{
    if(ui->KeepAspectRatio->isChecked()==true && hc==true)
    {
        QImage Resize(PhotoWindow::PhotoAddress()[PhotoWindow::Ps()]);

        if(ui->Height->value()>hvt)
        {
            th = th+1;

            if(w<=h)
            {
                pres=pres.fromImage(Resize.scaled(w+th ,h+th ,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
            }

            if(h<w)
            {
                pres=pres.fromImage(Resize.scaled(h+th ,w+th ,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }

            this->SetValue();
        }

        if(ui->Height->value()<hvt)
        {
            th=th-1;

            if(w<=h)
            {
                pres=pres.fromImage(Resize.scaled(w+th ,h+th ,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
            }

            if(h<w)
            {
                pres=pres.fromImage(Resize.scaled(h+th ,w+th ,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            }

            this->SetValue();
        }

        hvt=ui->Height->value();
    }
}

void ResizePhoto::SetValue()
{
    wc=false;
    hc=false;
    ui->Width->setValue(pres.width());
    ui->Height->setValue(pres.height());
    wc=true;
    hc=true;
}

void ResizePhoto::OKButton()
{
    rsWidth=ui->Width->value();
    rsHeight=ui->Height->value();

    resz=true;

    if(ui->KeepAspectRatio->isChecked()==true)
    {
        rekar=true;
    }
    else
    {
        rekar=false;
    }

    close();
}

void ResizePhoto::CancelButton()
{
    resz=false;
    close();
}

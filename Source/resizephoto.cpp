#include "resizephoto.h"
#include "ui_resizephoto.h"

#include <QStringList>
#include <QPixmap>

#include <QDebug>

extern int ps;
extern QStringList PhotoAddress;
int RSWidth=0,RSHeight=0;
bool rekar=false, resz=false;
int w=0,h=0;
int tw=0,th=0;
bool wc=true, hc=true;

resizephoto::resizephoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resizephoto)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //Photo Size
    {
        QPixmap PSize(PhotoAddress[ps]);

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

        ui->ResizeButtonBox->addButton(&OK, QDialogButtonBox::AcceptRole);
        ui->ResizeButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);
    }
}

resizephoto::~resizephoto()
{
    delete ui;
}

void resizephoto::on_Width_valueChanged()
{
    if(ui->KeepAspectRatio->isChecked()==true && wc==true)
    {
        QImage Resize(PhotoAddress[ps]);

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

void resizephoto::on_Height_valueChanged()
{
    if(ui->KeepAspectRatio->isChecked()==true && hc==true)
    {
        QImage Resize(PhotoAddress[ps]);

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

void resizephoto::SetValue()
{
    wc=false;
    hc=false;
    ui->Width->setValue(pres.width());
    ui->Height->setValue(pres.height());
    wc=true;
    hc=true;
}

void resizephoto::OKButton()
{
    RSWidth=ui->Width->value();
    RSHeight=ui->Height->value();

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

void resizephoto::CancelButton()
{
    resz=false;
    close();
}

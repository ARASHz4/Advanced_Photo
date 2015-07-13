#include "resizephoto.h"
#include "ui_resizephoto.h"

#include <QStringList>
#include <QPixmap>

int RSWidth=0,RSHeight=0;
bool resz=false;
extern int ps;
extern QStringList PhotoAddress;
int w=0,h=0;
int tw=0,th=0;
int wvt,hvt;
bool wc=true, hc=true, rekar=false;

resizephoto::resizephoto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resizephoto)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

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

void resizephoto::on_OkButton_clicked()
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

void resizephoto::on_CancelButton_clicked()
{
    resz=false;
    close();
}

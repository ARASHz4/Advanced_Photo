#include "about.h"
#include "ui_about.h"

#include <QMouseEvent>
#include <QPixmap>
#include <QDebug>

bool ds =false;

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

about::~about()
{
    delete ui;
}
void about::showEvent(QShowEvent *)
{
    ui->ApplicationNameLabel->setText(QApplication::applicationName());
    ui->ApplicationVersionLabel->setText(QApplication::applicationVersion());

    this->setWindowOpacity(0);

    show->setInterval(5);
    show->connect(show,SIGNAL(timeout()),this,SLOT(WindowShow()));
    show->start();
}

void about::WindowShow()
{
    this->setWindowOpacity(windowOpacity()+0.01);

    if(windowOpacity()==1.000000)
    {
        show->stop();
    }
}

void about::on_OkButton_clicked()
{
    hide->setInterval(2);
    hide->connect(hide,SIGNAL(timeout()),this,SLOT(WindowHide()));
    hide->start();
}

void about::mouseDoubleClickEvent(QMouseEvent *)
{
    if(ds == false)
    {
        ui->aboutIcon->setText("<html><head/><body><p><br/></p><p><span style="""
                               " font-size:12pt;"">" + tr("Developer :") + "</span></p><p align="""
                               "center""><span style="" font-size:12pt;"">" + tr("Arash Zare") + " ("
                               + QApplication::organizationName() + ")</span></p></body></html>");
        ds=true;
    }
    else if (ds == true)
    {
        ui->aboutIcon->setText(NULL);
        QPixmap ai(":/Icons/Icon.png");
        ui->aboutIcon->setPixmap(ai);
        ds=false;
    }
}

void about::WindowHide()
{
    this->setWindowOpacity(windowOpacity()-0.000001);

    if(windowOpacity()==0)
    {
        hide->stop();
        close();
    }
}

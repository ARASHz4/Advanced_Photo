#include "about.h"
#include "ui_about.h"
#include "advancedphoto.h"

#include <QMouseEvent>
#include <QPixmap>

bool ds = false;

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

about::~about()
{
    delete ui;
}

void about::showEvent(QShowEvent *)
{
    ui->ApplicationNameLabel->setText(AdvancedPhoto::applicationName());
    ui->ApplicationVersionLabel->setText(AdvancedPhoto::applicationVersion());

    this->setWindowOpacity(0);

    show.setInterval(5);
    show.connect(&show,SIGNAL(timeout()),this,SLOT(WindowShow()));
    show.start();
}

void about::WindowShow()
{
    this->setWindowOpacity(windowOpacity()+0.01);

    if(windowOpacity()==1.000000)
    {
        show.stop();
    }
}

void about::on_OkButton_clicked()
{
    hide.setInterval(2);
    hide.connect(&hide,SIGNAL(timeout()),this,SLOT(WindowHide()));
    hide.start();
}

void about::on_QtPushButton_clicked()
{
    AdvancedPhoto::aboutQt();
}

void about::mouseDoubleClickEvent(QMouseEvent *)
{
    if(ds == false)
    {
        ui->aboutIcon->setText("<html><head/><body><p><br/></p><p><span style="""
                               " font-size:12pt;"">" + tr("Developer :") + "</span></p><p align="""
                               "center""><span style="" font-size:12pt;"">" + tr("Arash Zare") + " ("
                               + AdvancedPhoto::organizationName() + ")</span></p></body></html>");
        ds=true;
    }
    else if (ds == true)
    {
        ui->aboutIcon->setText(NULL);
        ui->aboutIcon->setPixmap(QPixmap(":/Icons/Big Icon.png"));
        ds=false;
    }
}

void about::WindowHide()
{
    this->setWindowOpacity(windowOpacity()-0.000001);

    if(windowOpacity()==0)
    {
        hide.stop();
        close();
    }
}

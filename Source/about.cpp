#include "about.h"
#include "ui_about.h"
#include "advancedphoto.h"
#include "slsettings.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Start();
}

About::~About()
{
    delete ui;
}

void About::Start()
{
    ui->ApplicationNameLabel->setText(AdvancedPhoto::applicationName());

    if(SLSettings::Language() == QLocale::Persian)
    {
        QString Version = AdvancedPhoto::applicationVersion();
        Version.replace("0", "۰");
        Version.replace("1", "۱");
        Version.replace("2", "۲");
        Version.replace("3", "۳");
        Version.replace("4", "۴");
        Version.replace("5", "۵");
        Version.replace("6", "۶");
        Version.replace("7", "۷");
        Version.replace("8", "۸");
        Version.replace("9", "۹");
        Version.replace(".", "٫");

        ui->ApplicationVersionLabel->setText(Version);
    }
    else
    {
        ui->ApplicationVersionLabel->setText(AdvancedPhoto::applicationVersion());
    }

    ds = false;
}

void About::on_OkButton_clicked()
{
    close();
}

void About::on_QtPushButton_clicked()
{
    AdvancedPhoto::aboutQt();
}

void About::mouseDoubleClickEvent(QMouseEvent *)
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
        ui->aboutIcon->setPixmap(QPixmap(":/Icons/Icons/Big Icon.png"));
        ds=false;
    }
}

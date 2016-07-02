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
    ds = false;

    ui->ApplicationNameLabel->setText(AdvancedPhoto::applicationName());

    QFont font;
    font.setPointSize(ui->ApplicationNameLabel->font().pointSize() + 2);
    font.setBold(true);
    font.setKerning(true);

    ui->ApplicationNameLabel->setFont(font);

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

        ui->ApplicationVersionLabel->setText(tr("Version") + " " + Version);
    }
    else
    {
        ui->ApplicationVersionLabel->setText(tr("Version") + " " + AdvancedPhoto::applicationVersion());
    }

    ui->ApplicationBuiltOnDateLabel->setText(QString(tr("Built on") + " " __DATE__ " " __TIME__).replace("  "," "));
}

void About::on_CloseButton_clicked()
{
    close();
}

void About::on_AboutQtButton_clicked()
{
    AdvancedPhoto::aboutQt();
}

void About::mouseDoubleClickEvent(QMouseEvent *)
{
    if(ds == false)
    {
        ui->ApplicationIcon->setText("<html><head/><body><p><br/></p><p><span style="""
                               " font-size:12pt;"">" + tr("Developer :") + "</span></p><p align="""
                               "center""><span style="" font-size:12pt;"">" + tr("Arash Zare") + " ("
                               + AdvancedPhoto::organizationName() + ")</span></p></body></html>");
        ds=true;
    }
    else if (ds == true)
    {
        ui->ApplicationIcon->setText(NULL);
        ui->ApplicationIcon->setPixmap(QPixmap(":/Icons/Icons/Big Icon.png"));
        ds=false;
    }
}

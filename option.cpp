#include "option.h"
#include "ui_option.h"

#include <QSettings>
#include <QTranslator>
#include <QDesktopWidget>

//Variables:
int SlideshowSpeed;
bool kar, sgf ,oap;
//

option::option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::option)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //Option Window Size & Post Setting
    {
        QRect ScreenSize = QApplication::desktop()->screenGeometry();

        QSettings SettingsAP (QApplication::organizationName(), QApplication::applicationName());
        SettingsAP.beginGroup("OptionWindowSizePos");

        if((SettingsAP.value("window_posx").toInt() != 0 && SettingsAP.value("window_posy").toInt() != 0) &&
           (SettingsAP.value("window_sizew").toInt() <= ScreenSize.width()+10 && SettingsAP.value("window_sizeh").toInt() <= ScreenSize.height()+10))
        {
            this->setGeometry(SettingsAP.value("window_posx").toInt(), SettingsAP.value("window_posy").toInt(),
                              SettingsAP.value("window_sizew").toInt(), SettingsAP.value("window_sizeh").toInt());
        }
        SettingsAP.endGroup();

        SettingsAP.beginGroup("Option");

        if(SettingsAP.value("Language").toString() == "English")
        {
            ui->LanguageComboBox->setCurrentIndex(0);
        }
        else if(SettingsAP.value("Language").toString() == "پارسی")
        {
            ui->LanguageComboBox->setCurrentIndex(1);
        }
        SettingsAP.endGroup();
    }

    //Keep Aspect Ratio Setting
    {
        if(kar==true)
        {
           ui->KeepAspectRatioCheckBox->setChecked(true);
        }

        if(kar==false)
        {
            ui->KeepAspectRatioCheckBox->setChecked(false);
        }
    }

    //Load Other Photos in Folder Setting
    {
        if(oap==true)
        {
            ui->LoadPhotosFolder->setChecked(true);
        }

        if(oap==false)
        {
            ui->LoadPhotosFolder->setChecked(false);
        }
    }

    //Slideshow Setting
    {
        ui->SlideshowSpeed->setValue(SlideshowSpeed);

        if(sgf==true)
        {
            ui->slsFullscreen->setChecked(true);
        }

        if(sgf==false)
        {
            ui->slsFullscreen->setChecked(false);
        }
    }
}

option::~option()
{
    delete ui; 
}

void option::on_OkButton_clicked()
{
    QSettings SettingsAP (QApplication::organizationName(), QApplication::applicationName());
    SettingsAP.beginGroup("Option");

    //Keep Aspect Ratio
    {
        if(ui->KeepAspectRatioCheckBox->isChecked() == true)
        {
            kar=true;
        }

        if(ui->KeepAspectRatioCheckBox->isChecked() == false)
        {
            kar=false;
        }

        SettingsAP.setValue("KeepAspectRatio", kar);
    }

    //Load Photos Folder
    {
        if(ui->LoadPhotosFolder->isChecked() == true)
        {
            oap=true;
        }

        if(ui->LoadPhotosFolder->isChecked() == false)
        {
            oap=false;
        }

        SettingsAP.setValue("LoadPhotosFolder", oap);
    }

    //Language
    {
        QTranslator *Language = new QTranslator;

        if(ui->LanguageComboBox->currentText() == "English")
        {
            Language->load(":/Language/English.qm");
            QApplication::installTranslator(Language);
        }
        else if(ui->LanguageComboBox->currentText() == "پارسی")
        {
            Language->load(":/Language/Persian.qm");
            QApplication::installTranslator(Language);
        }
        else if(ui->LanguageComboBox->currentText() == "Español")
        {
            Language->load(":/Language/Spanish.qm");
            QApplication::installTranslator(Language);
        }

        SettingsAP.setValue("Language", ui->LanguageComboBox->currentText());
    }

    //Slideshow
    {
        SlideshowSpeed=ui->SlideshowSpeed->value();

        SettingsAP.setValue("SlideshowSpeed",SlideshowSpeed);

        if(ui->slsFullscreen->isChecked() == true)
        {
            sgf=true;
        }

        if(ui->slsFullscreen->isChecked() == false)
        {
            sgf=false;
        }

        SettingsAP.setValue("SlideshowFullscreen", sgf);
    }

    SettingsAP.endGroup();

    close(); 
}

void option::on_CancelButton_clicked()
{
    close();
}

void option::closeEvent (QCloseEvent *)
{
    QSettings SettingsAP (QApplication::organizationName(), QApplication::applicationName());

    SettingsAP.beginGroup("OptionWindowSizePos");

    SettingsAP.setValue("window_sizew", this->geometry().width());
    SettingsAP.setValue("window_sizeh", this->geometry().height());

    SettingsAP.setValue("window_posx", this->geometry().x());
    SettingsAP.setValue("window_posy", this->geometry().y());

    SettingsAP.endGroup();
}

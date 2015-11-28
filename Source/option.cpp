#include "option.h"
#include "ui_option.h"
#include "advancedphoto.h"

#include <QSettings>
#include <QTranslator>
#include <QDesktopWidget>

//Variables:
int SlideshowSpeed, ScreenshotDelay;
bool kar, sgf ,oap, sam;
//

option::option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::option)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //Option Window Size & Post Setting
    {
        QRect ScreenSize = AdvancedPhoto::desktop()->screenGeometry();

        QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
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
        else if(SettingsAP.value("Language").toString() == "Español")
        {
            ui->LanguageComboBox->setCurrentIndex(2);
        }
        else if(SettingsAP.value("Language").toString() == "中國傳統")
        {
            ui->LanguageComboBox->setCurrentIndex(3);
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
        else
        {
            ui->slsFullscreen->setChecked(false);
        }
    }

    //Screenshot
    {
        ui->ScreenshotDelaySpinBox->setValue(ScreenshotDelay);

        if(sam==true)
        {
            ui->ScreenshotAtuoMinimizeCheckBox->setChecked(true);
        }
        else
        {
            ui->ScreenshotAtuoMinimizeCheckBox->setChecked(false);
        }
    }

    ui->listWidgetOption->setCurrentRow(0);
}

option::~option()
{
    delete ui; 
}

void option::on_listWidgetOption_currentRowChanged(int currentRow)
{
    if(currentRow == 0)
    {
        ui->OptionGroupBox->setTitle(tr("General"));

        ui->KeepAspectRatioCheckBox->setVisible(true);
        ui->LoadPhotosFolder->setVisible(true);

        ui->LanguageLabel->setVisible(false);
        ui->LanguageComboBox->setVisible(false);
        ui->SppedLabel->setVisible(false);
        ui->SlideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
        ui->ScreenshotDelay->setVisible(false);
        ui->ScreenshotDelaySpinBox->setVisible(false);
        ui->SecLabel_2->setVisible(false);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(false);
    }
    else if (currentRow == 1)
    {
        ui->OptionGroupBox->setTitle(tr("Language"));

        ui->LanguageLabel->setVisible(true);
        ui->LanguageComboBox->setVisible(true);

        ui->KeepAspectRatioCheckBox->setVisible(false);
        ui->LoadPhotosFolder->setVisible(false);
        ui->SppedLabel->setVisible(false);
        ui->SlideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
        ui->ScreenshotDelay->setVisible(false);
        ui->ScreenshotDelaySpinBox->setVisible(false);
        ui->SecLabel_2->setVisible(false);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(false);
    }
    else if (currentRow == 2)
    {
        ui->OptionGroupBox->setTitle(tr("Slideshow"));

        ui->SppedLabel->setVisible(true);
        ui->SlideshowSpeed->setVisible(true);
        ui->SecLabel->setVisible(true);
        ui->slsFullscreen->setVisible(true);

        ui->KeepAspectRatioCheckBox->setVisible(false);
        ui->LoadPhotosFolder->setVisible(false);
        ui->LanguageLabel->setVisible(false);
        ui->LanguageComboBox->setVisible(false);
        ui->ScreenshotDelay->setVisible(false);
        ui->ScreenshotDelaySpinBox->setVisible(false);
        ui->SecLabel_2->setVisible(false);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(false);
    }
    else if (currentRow == 3)
    {
        ui->OptionGroupBox->setTitle(tr("Screenshot"));

        ui->ScreenshotDelay->setVisible(true);
        ui->ScreenshotDelaySpinBox->setVisible(true);
        ui->SecLabel_2->setVisible(true);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(true);

        ui->KeepAspectRatioCheckBox->setVisible(false);
        ui->LoadPhotosFolder->setVisible(false);
        ui->LanguageLabel->setVisible(false);
        ui->LanguageComboBox->setVisible(false);
        ui->SppedLabel->setVisible(false);
        ui->SlideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
    }
}

void option::on_OkButton_clicked()
{
    QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
    SettingsAP.beginGroup("Option");

    //General
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
            AdvancedPhoto::installTranslator(Language);
            AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
        }
        else if(ui->LanguageComboBox->currentText() == "پارسی")
        {
            Language->load(":/Language/Persian.qm");
            AdvancedPhoto::installTranslator(Language);
            AdvancedPhoto::setLayoutDirection(Qt::RightToLeft);
        }
        else if(ui->LanguageComboBox->currentText() == "Español")
        {
            Language->load(":/Language/Spanish.qm");
            AdvancedPhoto::installTranslator(Language);
            AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
        }
        else if(ui->LanguageComboBox->currentText() == "中國傳統")
        {
            Language->load(":/Language/Traditional Chinese.qm");
            AdvancedPhoto::installTranslator(Language);
            AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
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

    //Screenshot
    {
        ScreenshotDelay=ui->ScreenshotDelaySpinBox->value();

        SettingsAP.setValue("ScreenshotDelay", ScreenshotDelay);

        if(ui->ScreenshotAtuoMinimizeCheckBox->isChecked() == true)
        {
            sam=true;
        }

        if(ui->ScreenshotAtuoMinimizeCheckBox->isChecked() == false)
        {
            sam=false;
        }

        SettingsAP.setValue("ScreenshotAtuoMinimize", sam);
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
    QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());

    SettingsAP.beginGroup("OptionWindowSizePos");

    SettingsAP.setValue("window_sizew", this->geometry().width());
    SettingsAP.setValue("window_sizeh", this->geometry().height());

    SettingsAP.setValue("window_posx", this->geometry().x());
    SettingsAP.setValue("window_posy", this->geometry().y());

    SettingsAP.endGroup();
}

#include "option.h"
#include "ui_option.h"
#include "advancedphoto.h"

#include <QSettings>
#include <QTranslator>
#include <QDesktopWidget>

#include <QDebug>

//Variables:
int SlideshowSpeed, ScreenshotDelay;
bool kar, sgf ,oap, sam;
QString Language;
//

option::option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::option)
{
    ui->setupUi(this);

    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

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

        OK.setText(tr("OK"));
        Cancel.setText(tr("Cancel"));
        Apply.setText(tr("Apply"));
        RestoreDefaults.setText(tr("Restore Defaults"));

        OK.connect(&OK, SIGNAL(clicked()), this, SLOT(OKButton()));
        Cancel.connect(&Cancel, SIGNAL(clicked()), this, SLOT(CancelButton()));
        Apply.connect(&Apply, SIGNAL(clicked()), this, SLOT(ApplyButton()));
        RestoreDefaults.connect(&RestoreDefaults, SIGNAL(clicked()), this, SLOT(RestoreDefaultsButton()));

        ui->OptionButtonBox->addButton(&OK, QDialogButtonBox::AcceptRole);
        ui->OptionButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);
        ui->OptionButtonBox->addButton(&Apply, QDialogButtonBox::ApplyRole);
        ui->OptionButtonBox->addButton(&RestoreDefaults, QDialogButtonBox::ResetRole);
    }

    ui->listWidgetOption->setCurrentRow(0);

    LoadSettings();
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
        ui->LanguageRightToLeftCheckBox->setVisible(false);
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
        if(ui->LanguageComboBox->currentIndex() == 1)
        {
            ui->LanguageRightToLeftCheckBox->setVisible(true);
        }
        else
        {
            ui->LanguageRightToLeftCheckBox->setVisible(false);
        }

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
        ui->LanguageRightToLeftCheckBox->setVisible(false);
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
        ui->LanguageRightToLeftCheckBox->setVisible(false);
        ui->SppedLabel->setVisible(false);
        ui->SlideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
    }
}

void option::on_LanguageComboBox_currentIndexChanged(int index)
{
    if(index == 1)
    {
        ui->LanguageRightToLeftCheckBox->setVisible(true);
        ui->LanguageRightToLeftCheckBox->setChecked(true);
    }
    else
    {
        ui->LanguageRightToLeftCheckBox->setVisible(false);
        ui->LanguageRightToLeftCheckBox->setChecked(false);
    }
}

void option::LoadSettings()
{
    //General
    {
        if(kar==true)
        {
            ui->KeepAspectRatioCheckBox->setChecked(true);
        }
        else
        {
            ui->KeepAspectRatioCheckBox->setChecked(false);
        }

        if(oap==true)
        {
            ui->LoadPhotosFolder->setChecked(true);
        }
        else
        {
            ui->LoadPhotosFolder->setChecked(false);
        }
    }

    //Language
    {
        if(Language.contains("Automatic"))
        {
            ui->LanguageComboBox->setCurrentIndex(0);
        }
        else if(Language == "English")
        {
            ui->LanguageComboBox->setCurrentIndex(1);
        }
        else if(Language == "Persian RL" || Language == "Persian LR")
        {
            ui->LanguageComboBox->setCurrentIndex(2);

            if (Language == "Persian RL")
            {
                ui->LanguageRightToLeftCheckBox->setChecked(true);
            }
            else if (Language == "Persian LR")
            {
                ui->LanguageRightToLeftCheckBox->setChecked(false);
            }
        }
        else if(Language == "Spanish")
        {
            ui->LanguageComboBox->setCurrentIndex(3);
        }
        else if(Language == "Traditional Chinese")
        {
            ui->LanguageComboBox->setCurrentIndex(4);
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
}

void option::SaveSettings()
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
        if(ui->LanguageComboBox->currentIndex() == 0)
        {
            Language = "Automatic";
        }
        else if(ui->LanguageComboBox->currentIndex() == 1)
        {
            Language = "English";
        }
        else if(ui->LanguageComboBox->currentIndex() == 2)
        {
            if(ui->LanguageRightToLeftCheckBox->isChecked())
            {
                Language = "Persian RL";
            }
            else
            {
                Language = "Persian LR";
            }
        }
        else if(ui->LanguageComboBox->currentIndex() == 3)
        {
            Language = "Spanish";
        }
        else if(ui->LanguageComboBox->currentIndex() == 4)
        {
            Language = "Traditional Chinese";
        }

        QTranslator *Translator = new QTranslator;

        if(Language.contains("Automatic"))
        {
            if(QLocale::system().language() == QLocale::English)
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = "Automatic English";
            }
            else if(QLocale::system().language() == QLocale::Persian)
            {
                Translator->load(":/Language/Persian RL.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = "Automatic Persian RL";
            }
            else if(QLocale::system().language() == QLocale::Spanish)
            {
                Translator->load(":/Language/Spanish.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = "Automatic Spanish";
            }
            else if(QLocale::system().language() == QLocale::Chinese)
            {
                Translator->load(":/Language/Traditional Chinese.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = "Automatic Traditional Chinese";
            }

            SettingsAP.setValue("Language", "Automatic");
        }
        else
        {
            Translator->load(":/Language/" + Language + ".qm");
            AdvancedPhoto::installTranslator(Translator);

            SettingsAP.setValue("Language", Language);
        }

        if(Language.contains("English") || Language.contains("Persian LR")
        || Language.contains("Spanish") || Language.contains("Traditional Chinese"))
        {
            AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
        }
        else if(Language.contains("Persian RL"))
        {
            AdvancedPhoto::setLayoutDirection(Qt::RightToLeft);
        }
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
}

void option::OKButton()
{
    SaveSettings();

    close();
}

void option::CancelButton()
{
    close();
}

void option::ApplyButton()
{
    SaveSettings();
}

void option::RestoreDefaultsButton()
{
    kar = true;
    oap = true;
    Language = "Automatic";
    SlideshowSpeed = 2;
    sgf = false;
    ScreenshotDelay = 3;
    sam = true;

    LoadSettings();
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

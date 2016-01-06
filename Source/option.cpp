#include "option.h"
#include "ui_option.h"
#include "advancedphoto.h"
#include "slsettings.h"

#include <QTranslator>
#include <QDesktopWidget>

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
           (SettingsAP.value("window_sizew").toInt() <= ScreenSize.width()+10
            && SettingsAP.value("window_sizeh").toInt() <= ScreenSize.height()+10))
        {
            this->setGeometry(SettingsAP.value("window_posx").toInt(), SettingsAP.value("window_posy").toInt(),
                              SettingsAP.value("window_sizew").toInt(), SettingsAP.value("window_sizeh").toInt());
        }
        SettingsAP.endGroup();

        OK.connect(&OK, SIGNAL(clicked()), this, SLOT(OKButton()));
        Cancel.connect(&Cancel, SIGNAL(clicked()), this, SLOT(CancelButton()));
        Apply.connect(&Apply, SIGNAL(clicked()), this, SLOT(ApplyButton()));
        RestoreDefaults.connect(&RestoreDefaults, SIGNAL(clicked()), this, SLOT(RestoreDefaultsButton()));
        OK.setText(tr("OK"));
        Cancel.setText(tr("Cancel"));
        Apply.setText(tr("Apply"));
        RestoreDefaults.setText(tr("Restore Defaults"));
        OK.setDefault(true);

        ui->OptionButtonBox->addButton(&OK, QDialogButtonBox::AcceptRole);
        ui->OptionButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);
        ui->OptionButtonBox->addButton(&Apply, QDialogButtonBox::ApplyRole);
        ui->OptionButtonBox->addButton(&RestoreDefaults, QDialogButtonBox::ResetRole);
    }

    ui->listWidgetOption->setCurrentRow(0);
    ui->LanguageComboBox->insertSeparator(1);

    Load();
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
        ui->slideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
        ui->screenshotDelay->setVisible(false);
        ui->screenshotDelaySpinBox->setVisible(false);
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
        ui->slideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
        ui->screenshotDelay->setVisible(false);
        ui->screenshotDelaySpinBox->setVisible(false);
        ui->SecLabel_2->setVisible(false);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(false);
    }
    else if (currentRow == 2)
    {
        ui->OptionGroupBox->setTitle(tr("Slideshow"));

        ui->SppedLabel->setVisible(true);
        ui->slideshowSpeed->setVisible(true);
        ui->SecLabel->setVisible(true);
        ui->slsFullscreen->setVisible(true);

        ui->KeepAspectRatioCheckBox->setVisible(false);
        ui->LoadPhotosFolder->setVisible(false);
        ui->LanguageLabel->setVisible(false);
        ui->LanguageComboBox->setVisible(false);
        ui->screenshotDelay->setVisible(false);
        ui->screenshotDelaySpinBox->setVisible(false);
        ui->SecLabel_2->setVisible(false);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(false);
    }
    else if (currentRow == 3)
    {
        ui->OptionGroupBox->setTitle(tr("Screenshot"));

        ui->screenshotDelay->setVisible(true);
        ui->screenshotDelaySpinBox->setVisible(true);
        ui->SecLabel_2->setVisible(true);
        ui->ScreenshotAtuoMinimizeCheckBox->setVisible(true);

        ui->KeepAspectRatioCheckBox->setVisible(false);
        ui->LoadPhotosFolder->setVisible(false);
        ui->LanguageLabel->setVisible(false);
        ui->LanguageComboBox->setVisible(false);
        ui->SppedLabel->setVisible(false);
        ui->slideshowSpeed->setVisible(false);
        ui->SecLabel->setVisible(false);
        ui->slsFullscreen->setVisible(false);
    }
}

void option::Load()
{
    //General
    {
        if(SLSettings::Kar() == true)
        {
            ui->KeepAspectRatioCheckBox->setChecked(true);
        }
        else
        {
            ui->KeepAspectRatioCheckBox->setChecked(false);
        }

        if(SLSettings::Oap()==true)
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
        if(SLSettings::AutomaticLanguage() == true)
        {
            ui->LanguageComboBox->setCurrentIndex(0);
        }
        else
        {
            if(SLSettings::Language() == QLocale::English)
            {
                ui->LanguageComboBox->setCurrentIndex(2);
            }
            else if(SLSettings::Language() == QLocale::Persian)
            {
                ui->LanguageComboBox->setCurrentIndex(3);
            }
            else if(SLSettings::Language() == QLocale::Spanish)
            {
                ui->LanguageComboBox->setCurrentIndex(4);
            }
            else if(SLSettings::Language() == QLocale::Chinese)
            {
                ui->LanguageComboBox->setCurrentIndex(5);
            }
        }
    }

    //Slideshow Setting
    {
        ui->slideshowSpeed->setValue(SLSettings::SlideshowSpeed());

        if(SLSettings::Sgf()==true)
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
        ui->screenshotDelaySpinBox->setValue(SLSettings::ScreenshotDelay());

        if(SLSettings::Sam()==true)
        {
            ui->ScreenshotAtuoMinimizeCheckBox->setChecked(true);
        }
        else
        {
            ui->ScreenshotAtuoMinimizeCheckBox->setChecked(false);
        }
    }
}

void option::Save()
{
    //General
    {
        if(ui->KeepAspectRatioCheckBox->isChecked() == true)
        {
            SLSettings::setKar(true);
        }

        if(ui->KeepAspectRatioCheckBox->isChecked() == false)
        {
            SLSettings::setKar(false);
        }

        if(ui->LoadPhotosFolder->isChecked() == true)
        {
            SLSettings::setOap(true);
        }

        if(ui->LoadPhotosFolder->isChecked() == false)
        {
            SLSettings::setOap(false);
        }
    }

    //Language
    {
        if(ui->LanguageComboBox->currentIndex() == 0)
        {
            SLSettings::setLanguage(0);
        }
        else if(ui->LanguageComboBox->currentIndex() == 2)
        {
            SLSettings::setLanguage(QLocale::English);
        }
        else if(ui->LanguageComboBox->currentIndex() == 3)
        {
            SLSettings::setLanguage(QLocale::Persian);
        }
        else if(ui->LanguageComboBox->currentIndex() == 4)
        {
            SLSettings::setLanguage(QLocale::Spanish);
        }
        else if(ui->LanguageComboBox->currentIndex() == 5)
        {
            SLSettings::setLanguage(QLocale::Chinese);
        }

        QTranslator *Translator = new QTranslator;

        if(SLSettings::Language() == 0)
        {
            if(QLocale::system().language() == QLocale::English)
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::English);
            }
            else if(QLocale::system().language() == QLocale::Persian)
            {
                Translator->load(":/Language/Persian.qm");
                AdvancedPhoto::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::Persian);
            }
            else if(QLocale::system().language() == QLocale::Spanish)
            {
                Translator->load(":/Language/Spanish.qm");
                AdvancedPhoto::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::Spanish);
            }
            else if(QLocale::system().language() == QLocale::Chinese)
            {
                Translator->load(":/Language/Traditional Chinese.qm");
                AdvancedPhoto::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::Chinese);
            }
            else
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::English);
            }

            SLSettings::setAutomaticLanguage(true);
        }
        else
        {
            if(SLSettings::Language() == QLocale::English)
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);
            }
            else if(SLSettings::Language() == QLocale::Persian)
            {
                Translator->load(":/Language/Persian.qm");
                AdvancedPhoto::installTranslator(Translator);
            }
            else if(SLSettings::Language() == QLocale::Spanish)
            {
                Translator->load(":/Language/Spanish.qm");
                AdvancedPhoto::installTranslator(Translator);
            }
            else if(SLSettings::Language() == QLocale::Chinese)
            {
                Translator->load(":/Language/Traditional Chinese.qm");
                AdvancedPhoto::installTranslator(Translator);
            }

            SLSettings::setAutomaticLanguage(false);
        }

        if(SLSettings::Language() == QLocale::English || SLSettings::Language() == QLocale::Spanish || SLSettings::Language() == QLocale::Chinese)
        {
            AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
        }
        else if(SLSettings::Language() == QLocale::Persian)
        {
            AdvancedPhoto::setLayoutDirection(Qt::RightToLeft);
        }
    }

    //Slideshow
    {
        SLSettings::setSlideshowSpeed(ui->slideshowSpeed->value());

        if(ui->slsFullscreen->isChecked() == true)
        {
            SLSettings::setSgf(true);
        }

        if(ui->slsFullscreen->isChecked() == false)
        {
            SLSettings::setSgf(false);
        }
    }

    //Screenshot
    {
        SLSettings::setScreenshotDelay(ui->screenshotDelaySpinBox->value());

        if(ui->ScreenshotAtuoMinimizeCheckBox->isChecked() == true)
        {
            SLSettings::setSam(true);
        }

        if(ui->ScreenshotAtuoMinimizeCheckBox->isChecked() == false)
        {
            SLSettings::setSam(false);
        }
    }

    SLSettings Ssettings;
    Ssettings.SaveSettings();
}

void option::OKButton()
{
    Save();
    close();
}

void option::CancelButton()
{
    close();
}

void option::ApplyButton()
{
    Save();

    ui->retranslateUi(this);
    OK.setText(tr("OK"));
    Cancel.setText(tr("Cancel"));
    Apply.setText(tr("Apply"));
    RestoreDefaults.setText(tr("Restore Defaults"));
}

void option::RestoreDefaultsButton()
{
    SLSettings::setKar(true);
    SLSettings::setOap(true);
    SLSettings::setAutomaticLanguage(true);
    SLSettings::setLanguage(0);
    SLSettings::setSlideshowSpeed(2);
    SLSettings::setSgf(false);
    SLSettings::setScreenshotDelay(3);
    SLSettings::setSam(true);

    Load();
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

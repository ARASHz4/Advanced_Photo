#include "option.h"
#include "ui_option.h"
#include "advancedphoto.h"

#include <QSettings>
#include <QTranslator>
#include <QDesktopWidget>

//Variables:
int SlideshowSpeed, ScreenshotDelay, Language;
bool kar, sgf, oap, sam, AutomaticLanguage;
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
        if(AutomaticLanguage == true)
        {
            ui->LanguageComboBox->setCurrentIndex(0);
        }
        else
        {
            if(Language == QLocale::English)
            {
                ui->LanguageComboBox->setCurrentIndex(2);
            }
            else if(Language == QLocale::Persian)
            {
                ui->LanguageComboBox->setCurrentIndex(3);
            }
            else if(Language == QLocale::Spanish)
            {
                ui->LanguageComboBox->setCurrentIndex(4);
            }
            else if(Language == QLocale::Chinese)
            {
                ui->LanguageComboBox->setCurrentIndex(5);
            }
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
            Language = 0;
        }
        else if(ui->LanguageComboBox->currentIndex() == 2)
        {
            Language = QLocale::English;
        }
        else if(ui->LanguageComboBox->currentIndex() == 3)
        {
            Language = QLocale::Persian;
        }
        else if(ui->LanguageComboBox->currentIndex() == 4)
        {
            Language = QLocale::Spanish;
        }
        else if(ui->LanguageComboBox->currentIndex() == 5)
        {
            Language = QLocale::Chinese;
        }

        QTranslator *Translator = new QTranslator;

        if(Language == 0)
        {
            if(QLocale::system().language() == QLocale::English)
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = QLocale::English;
            }
            else if(QLocale::system().language() == QLocale::Persian)
            {
                Translator->load(":/Language/Persian.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = QLocale::Persian;
            }
            else if(QLocale::system().language() == QLocale::Spanish)
            {
                Translator->load(":/Language/Spanish.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = QLocale::Spanish;
            }
            else if(QLocale::system().language() == QLocale::Chinese)
            {
                Translator->load(":/Language/Traditional Chinese.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = QLocale::Chinese;
            }
            else
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);

                Language = QLocale::English;
            }

            AutomaticLanguage = true;
            SettingsAP.setValue("Language", 0);
        }
        else
        {
            if(Language == QLocale::English)
            {
                Translator->load(":/Language/English.qm");
                AdvancedPhoto::installTranslator(Translator);
            }
            else if(Language == QLocale::Persian)
            {
                Translator->load(":/Language/Persian.qm");
                AdvancedPhoto::installTranslator(Translator);
            }
            else if(Language == QLocale::Spanish)
            {
                Translator->load(":/Language/Spanish.qm");
                AdvancedPhoto::installTranslator(Translator);
            }
            else if(Language == QLocale::Chinese)
            {
                Translator->load(":/Language/Traditional Chinese.qm");
                AdvancedPhoto::installTranslator(Translator);
            }

            AutomaticLanguage = false;
            SettingsAP.setValue("Language", Language);
        }

        if(Language == QLocale::English || Language == QLocale::Spanish || Language == QLocale::Chinese)
        {
            AdvancedPhoto::setLayoutDirection(Qt::LeftToRight);
        }
        else if(Language == QLocale::Persian)
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

    ui->retranslateUi(this);
    OK.setText(tr("OK"));
    Cancel.setText(tr("Cancel"));
    Apply.setText(tr("Apply"));
    RestoreDefaults.setText(tr("Restore Defaults"));
}

void option::RestoreDefaultsButton()
{
    kar = true;
    oap = true;
    AutomaticLanguage = true;
    Language = 0;
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

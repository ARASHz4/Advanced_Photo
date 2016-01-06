#include "slsettings.h"
#include "advancedphoto.h"

#include <QSettings>
#include <QDesktopWidget>

#include <QDebug>

//Variables:
bool SLSettings::kar, SLSettings::sgf, SLSettings::oap, SLSettings::sam;
int SLSettings::slideshowSpeed, SLSettings::screenshotDelay;
int SLSettings::language;
bool SLSettings::automaticLanguage;
//

SLSettings::SLSettings()
{

}

void SLSettings::setKar(bool value)
{
    kar = value;
}

bool SLSettings::Kar()
{
    return kar;
}

void SLSettings::setSgf(bool value)
{
    sgf = value;
}

bool SLSettings::Sgf()
{
    return sgf;
}

void SLSettings::setOap(bool value)
{
    oap = value;
}

bool SLSettings::Oap()
{
    return oap;
}

void SLSettings::setSam(bool value)
{
    sam = value;
}

bool SLSettings::Sam()
{
    return sam;
}

void SLSettings::setSlideshowSpeed(int value)
{
    slideshowSpeed = value;
}

int SLSettings::SlideshowSpeed()
{
    return slideshowSpeed;
}

void SLSettings::setScreenshotDelay(int value)
{
    screenshotDelay = value;
}

int SLSettings::ScreenshotDelay()
{
    return screenshotDelay;
}

void SLSettings::setLanguage(int value)
{
    language = value;
}

int SLSettings::Language()
{
    return language;
}

void SLSettings::setAutomaticLanguage(bool value)
{
    automaticLanguage = value;
}

bool SLSettings::AutomaticLanguage()
{
    return automaticLanguage;
}

void SLSettings::LoadSettings()
{
    QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
    SettingsAP.beginGroup("Option");

    //General
    {
        if((QString(SettingsAP.value("KeepAspectRatio").toString()).isEmpty())
                || (QString(SettingsAP.value("KeepAspectRatio").toString())!="true"
                    && QString(SettingsAP.value("KeepAspectRatio").toString())!="false"))
        {
            SettingsAP.setValue("KeepAspectRatio", "true");
        }

        SLSettings::setKar(SettingsAP.value("KeepAspectRatio").toBool());

        if((QString(SettingsAP.value("LoadPhotosFolder").toString()).isEmpty())
                || (QString(SettingsAP.value("LoadPhotosFolder").toString())!="true"
                    && QString(SettingsAP.value("LoadPhotosFolder").toString())!="false"))
        {
            SettingsAP.setValue("LoadPhotosFolder", "true");
        }

        SLSettings::setOap(SettingsAP.value("LoadPhotosFolder").toBool());
    }

    //Language
    {
        if(!SettingsAP.value("Language").toString().isEmpty() &&
                (SettingsAP.value("Language").toInt() == 0
                 || SettingsAP.value("Language").toInt() == QLocale::English
                 || SettingsAP.value("Language").toInt() == QLocale::Persian
                 || SettingsAP.value("Language").toInt() == QLocale::Spanish
                 || SettingsAP.value("Language").toInt() == QLocale::Chinese))
        {
            SLSettings::setLanguage(SettingsAP.value("Language").toInt());
        }
        else
        {
            SLSettings::setLanguage(0);
            SettingsAP.setValue("Language", SLSettings::Language());
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
        SLSettings::setSlideshowSpeed(SettingsAP.value("slideshowSpeed").toInt());

        if(SLSettings::SlideshowSpeed() <= 0 || SLSettings::SlideshowSpeed() > 99)
        {
            SLSettings::setSlideshowSpeed(2);

            SettingsAP.setValue("slideshowSpeed",SLSettings::SlideshowSpeed());
        }

        if((QString(SettingsAP.value("SlideshowFullscreen").toString()).isEmpty())
                || (QString(SettingsAP.value("SlideshowFullscreen").toString())!="true"
                    && QString(SettingsAP.value("SlideshowFullscreen").toString())!="false"))
        {
            SettingsAP.setValue("SlideshowFullscreen", "false");
        }

        SLSettings::setSgf(SettingsAP.value("SlideshowFullscreen").toBool());
    }

    //Screenshot
    {
        SLSettings::setScreenshotDelay(SettingsAP.value("screenshotDelay").toInt());

        if(SLSettings::ScreenshotDelay() <= 0 || SLSettings::ScreenshotDelay() > 60)
        {
            SLSettings::setScreenshotDelay(3);

            SettingsAP.setValue("screenshotDelay", SLSettings::ScreenshotDelay());
        }

        if((QString(SettingsAP.value("ScreenshotAtuoMinimize").toString()).isEmpty())
                || (QString(SettingsAP.value("ScreenshotAtuoMinimize").toString())!="true"
                    && QString(SettingsAP.value("ScreenshotAtuoMinimize").toString())!="false"))
        {
            SettingsAP.setValue("ScreenshotAtuoMinimize", "true");
        }

        SLSettings::setSam(SettingsAP.value("ScreenshotAtuoMinimize").toBool());
    }

    SettingsAP.endGroup();
}

void SLSettings::SaveSettings()
{
    QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
    SettingsAP.beginGroup("Option");

    SettingsAP.setValue("KeepAspectRatio", SLSettings::Kar());

    SettingsAP.setValue("LoadPhotosFolder", SLSettings::Oap());

    if(SLSettings::AutomaticLanguage() == true)
    {
        SettingsAP.setValue("Language", 0);
    }
    else
    {
        SettingsAP.setValue("Language", SLSettings::Language());
    }

    SettingsAP.setValue("slideshowSpeed",SLSettings::SlideshowSpeed());

    SettingsAP.setValue("SlideshowFullscreen", SLSettings::Sgf());

    SettingsAP.setValue("screenshotDelay", SLSettings::ScreenshotDelay());

    SettingsAP.setValue("ScreenshotAtuoMinimize", SLSettings::Sam());

    SettingsAP.endGroup();
}

void SLSettings::LoadPhotoWindow()
{

}

void SLSettings::SavePhotoWindow()
{

}

int SLSettings::LoadOptionWindow()
{
    QRect ScreenSize = AdvancedPhoto::desktop()->screenGeometry();

    QSettings SettingsAP (AdvancedPhoto::organizationName(), AdvancedPhoto::applicationName());
    SettingsAP.beginGroup("OptionWindowSizePos");

    if((SettingsAP.value("window_posx").toInt() != 0 && SettingsAP.value("window_posy").toInt() != 0) &&
       (SettingsAP.value("window_sizew").toInt() <= ScreenSize.width()+10
        && SettingsAP.value("window_sizeh").toInt() <= ScreenSize.height()+10))
    {
        return SettingsAP.value("window_posx").toInt();
        return SettingsAP.value("window_posy").toInt();
        return SettingsAP.value("window_sizew").toInt();
        return SettingsAP.value("window_sizeh").toInt();
    }
    SettingsAP.endGroup();
}

void SLSettings::SaveOptionWindow()
{

}

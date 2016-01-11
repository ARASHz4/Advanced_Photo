#ifndef SLSETTINGS_H
#define SLSETTINGS_H

#include "advancedphoto.h"

class SLSettings
{
public:
    SLSettings();

    static void setKar(bool value);

    static bool Kar();

    static void setSgf(bool value);

    static bool Sgf();

    static void setOap(bool value);

    static bool Oap();

    static void setSam(bool value);

    static bool Sam();

    static void setSlideshowSpeed(int value);

    static int SlideshowSpeed();

    static void setScreenshotDelay(int value);

    static int ScreenshotDelay();

    static void setLanguage(int value);

    static int Language();

    static void setAutomaticLanguage(bool value);

    static bool AutomaticLanguage();

    void LoadSettings();

    void SaveSettings();

    static std::tuple<int, int, int, int, int, bool, bool> LoadPhotoWindow();

    static void SavePhotoWindow(int x, int y, int w, int h, int toolBarArea, bool window_max, bool window_fuls);

    static std::tuple<int, int, int, int> LoadOptionWindow();

    static void SaveOptionWindow(int x, int y, int w, int h);

private:
    static bool kar, sgf, oap, sam, automaticLanguage;
    static int slideshowSpeed, screenshotDelay, language;
};

#endif // SLSETTINGS_H

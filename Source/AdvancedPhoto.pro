#-------------------------------------------------
#
# Project created by ARASHz4 2014-08-19T17:56:27
#
#-------------------------------------------------

QT += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Advanced Photo"
TEMPLATE = app

SOURCES += main.cpp\
    option.cpp \
    about.cpp \
    photowindow.cpp \
    resizephoto.cpp \
    photoinfo.cpp

HEADERS  += \
    option.h \
    about.h \
    photowindow.h \
    resizephoto.h \
    photoinfo.h

FORMS    += \
    option.ui \
    about.ui \
    photowindow.ui \
    resizephoto.ui \
    photoinfo.ui

RESOURCES += \
    Icon.qrc \
    Language.qrc

win32: RC_FILE = Windows/APWinRes.rc

mac: QMAKE_INFO_PLIST = Mac/APInfo.plist
mac: ICON = Mac/APIcon.icns

linux: ICON = Linux/APIcon.png

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/Android

OTHER_FILES += \
    Windows/APWinRes.rc \
    Windows/version.h \
    Windows/APIcon.ico \
    Windows/APIFile.ico \
    Mac/APInfo.plist \
    Mac/APIcon.icns \
    Mac/APIFile.icns \
    Linux/APIcon.png

DISTFILES += \
    Android/gradle/wrapper/gradle-wrapper.jar \
    Android/AndroidManifest.xml \
    Android/res/values/libs.xml \
    Android/build.gradle \
    Android/gradle/wrapper/gradle-wrapper.properties \
    Android/gradlew \
    Android/gradlew.bat \
    Android/res/drawable-hdpi/icon.png \
    Android/res/drawable-ldpi/icon.png \
    Android/res/drawable-mdpi/icon.png

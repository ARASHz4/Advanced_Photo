#-------------------------------------------------
#
# Project created by ARASHz4 2014-08-19T17:56:27
#
#-------------------------------------------------

QT += core gui printsupport svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Advanced Photo"
TEMPLATE = app

CONFIG += c++11

win32
{
    RC_FILE = Windows/APWinRes.rc
    CONFIG -= embed_manifest_exe
}

mac
{
    QMAKE_INFO_PLIST = Mac/APInfo.plist
    ICON = Mac/APIcon.icns
}

SOURCES += main.cpp\
    about.cpp \
    photowindow.cpp \
    resizephoto.cpp \
    photoinfo.cpp \
    advancedphoto.cpp \
    goto.cpp \
    slsettings.cpp \
    options.cpp

HEADERS  += \
    about.h \
    photowindow.h \
    resizephoto.h \
    photoinfo.h \
    advancedphoto.h \
    goto.h \
    slsettings.h \
    options.h

FORMS    += \
    about.ui \
    photowindow.ui \
    resizephoto.ui \
    photoinfo.ui \
    goto.ui \
    options.ui

RESOURCES += \
    apresource.qrc

DISTFILES += \
    Windows/APWinRes.rc \
    Windows/version.h \
    Windows/APIcon.ico \
    Windows/APIFile.ico \
    "Windows/Advanced Photo.exe.manifest" \
    Mac/APInfo.plist \
    Mac/APIcon.icns \
    Mac/APIFile.icns \
    Linux/AdvancedPhoto.desktop \
    Linux/APIcon.png \

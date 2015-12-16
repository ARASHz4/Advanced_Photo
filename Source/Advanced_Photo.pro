#-------------------------------------------------
#
# Project created by ARASHz4 2014-08-19T17:56:27
#
#-------------------------------------------------

QT += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "Advanced Photo"
TEMPLATE = app

win32: RC_FILE = Windows/APWinRes.rc

mac: QMAKE_INFO_PLIST = Mac/APInfo.plist
mac: ICON = Mac/APIcon.icns

SOURCES += main.cpp\
    option.cpp \
    about.cpp \
    photowindow.cpp \
    resizephoto.cpp \
    photoinfo.cpp \
    advancedphoto.cpp \
    goto.cpp

HEADERS  += \
    option.h \
    about.h \
    photowindow.h \
    resizephoto.h \
    photoinfo.h \
    advancedphoto.h \
    goto.h

FORMS    += \
    option.ui \
    about.ui \
    photowindow.ui \
    resizephoto.ui \
    photoinfo.ui \
    goto.ui

RESOURCES += \
    Icon.qrc \
    Language.qrc

OTHER_FILES += \
    Windows/APWinRes.rc \
    Windows/version.h \
    Windows/APIcon.ico \
    Windows/APIFile.ico \
    Mac/APInfo.plist \
    Mac/APIcon.icns \
    Mac/APIFile.icns

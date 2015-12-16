#ifndef ADVANCEDPHOTO_H
#define ADVANCEDPHOTO_H

#include "photowindow.h"
#include "ui_photowindow.h"

#include <QApplication>
#include <QTranslator>

class AdvancedPhoto : public QApplication
{
    Q_OBJECT

public:
    AdvancedPhoto(int &argc, char *argv[]);

#if defined(Q_OS_MAC)
    bool event(QEvent *event);
#endif

    PhotoWindow photowindow;

private:
    QStringList args;

public slots:
    void StartApplication();
};

#endif // ADVANCEDPHOTO_H

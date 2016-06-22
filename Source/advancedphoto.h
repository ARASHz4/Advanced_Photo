#ifndef ADVANCEDPHOTO_H
#define ADVANCEDPHOTO_H

#include <QApplication>
#include <cstdlib>
#include <QTranslator>
#include <QFileOpenEvent>
#include <QMessageBox>

#include "photowindow.h"

class AdvancedPhoto : public QApplication
{
    Q_OBJECT

public:
    AdvancedPhoto(int &argc, char *argv[]);

private:
    #if defined(Q_OS_MAC)
    bool event(QEvent *event);
    #endif

    QStringList args;

    PhotoWindow photowindow;

public slots:
    void StartApplication();

};

#endif // ADVANCEDPHOTO_H

#ifndef ADVANCEDPHOTO_H
#define ADVANCEDPHOTO_H

#include "photowindow.h"
#include "ui_photowindow.h"

#include <QApplication>

class AdvancedPhoto : public QApplication
{
    Q_OBJECT

public:
    AdvancedPhoto(int argc, char *argv[]);

    bool event(QEvent *event);

public slots:
    void StartApp();

private:
    PhotoWindow photowindow;

    QStringList args;
};

#endif // ADVANCEDPHOTO_H

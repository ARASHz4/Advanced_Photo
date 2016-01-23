#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private slots:
    void Start();

    void on_OkButton_clicked();

    void on_QtPushButton_clicked();

    void mouseDoubleClickEvent(QMouseEvent *);

    void WindowShow();

    void WindowHide();

private:
    Ui::About *ui;

    bool ds;

    QTimer hide;
    QTimer show;
};

#endif // ABOUT_H

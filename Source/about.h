#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

    QTimer *hide = new QTimer();

    QTimer *show = new QTimer();

private slots:
    void showEvent(QShowEvent *);

    void on_OkButton_clicked();

    void mouseDoubleClickEvent(QMouseEvent *);

    void WindowShow();

    void WindowHide();

private:
    Ui::about *ui;
};

#endif // ABOUT_H

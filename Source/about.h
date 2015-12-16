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

    QTimer hide;

    QTimer show;

private slots:
    void showEvent(QShowEvent *);

    void on_OkButton_clicked();

    void on_QtPushButton_clicked();

    void mouseDoubleClickEvent(QMouseEvent *);

    void WindowShow();

    void WindowHide();

private:
    Ui::about *ui;
};

#endif // ABOUT_H

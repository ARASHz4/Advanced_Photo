#ifndef GOTO_H
#define GOTO_H

#include <QDialog>

namespace Ui {
class GoTo;
}

class GoTo : public QDialog
{
    Q_OBJECT

public:
    explicit GoTo(QWidget *parent = 0);
    ~GoTo();

private slots:
    void showEvent(QShowEvent *);

    void on_GoPushButton_clicked();

    void on_CancelPushButton_clicked();

private:
    Ui::GoTo *ui;
};

#endif // GOTO_H

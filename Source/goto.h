#ifndef GOTO_H
#define GOTO_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class GoTo;
}

class GoTo : public QDialog
{
    Q_OBJECT

public:
    explicit GoTo(QWidget *parent = 0);
    ~GoTo();

private:
    Ui::GoTo *ui;

    QPushButton Go, Cancel;

private slots:
    void Start();

    void GoButton();

    void CancelButton();

};

#endif // GOTO_H

#ifndef PHOTOINFO_H
#define PHOTOINFO_H

#include <QDialog>

namespace Ui {
class photoinfo;
}

class photoinfo : public QDialog
{
    Q_OBJECT

public:
    explicit photoinfo(QWidget *parent = 0);
    ~photoinfo();

private slots:
    void showEvent(QShowEvent *);

    void on_OkButton_clicked();

private:
    Ui::photoinfo *ui;
};

#endif // PHOTOINFO_H

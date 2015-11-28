#ifndef OPTION_H
#define OPTION_H

#include <QDialog>

namespace Ui {
class option;
}

class option : public QDialog
{
    Q_OBJECT

public:
    explicit option(QWidget *parent = 0);
    ~option();

private slots:
    void on_listWidgetOption_currentRowChanged(int currentRow);

    void on_OkButton_clicked();

    void on_CancelButton_clicked();

    void closeEvent (QCloseEvent *);

private:
    Ui::option *ui;
};

#endif // OPTION_H

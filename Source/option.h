#ifndef OPTION_H
#define OPTION_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class option;
}

class option : public QDialog
{
    Q_OBJECT

public:
    explicit option(QWidget *parent = 0);
    ~option();

private:
    Ui::option *ui;

    QPushButton OK, Cancel, Apply, RestoreDefaults;

private slots:
    void showEvent(QShowEvent *);

    void on_listWidgetOption_currentRowChanged(int currentRow);

    void Load();

    void Save();

    void OKButton();

    void CancelButton();

    void ApplyButton();

    void RestoreDefaultsButton();

    void closeEvent (QCloseEvent *);

};

#endif // OPTION_H

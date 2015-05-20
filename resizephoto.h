#ifndef RESIZEPHOTO_H
#define RESIZEPHOTO_H

#include <QDialog>

namespace Ui {
class resizephoto;
}

class resizephoto : public QDialog
{
    Q_OBJECT

public:
    explicit resizephoto(QWidget *parent = 0);
    ~resizephoto();

    QPixmap pres;

private slots:
    void on_Width_valueChanged();

    void on_Height_valueChanged();

    void SetValue();

    void on_OkButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::resizephoto *ui;
};

#endif // RESIZEPHOTO_H

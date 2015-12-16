#ifndef RESIZEPHOTO_H
#define RESIZEPHOTO_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class resizephoto;
}

class resizephoto : public QDialog
{
    Q_OBJECT

public:
    explicit resizephoto(QWidget *parent = 0);
    ~resizephoto();

private:
    Ui::resizephoto *ui;

    int wvt,hvt;
    QPixmap pres;
    QPushButton OK, Cancel;

private slots:
    void on_Width_valueChanged();

    void on_Height_valueChanged();

    void SetValue();

    void OKButton();

    void CancelButton();

};

#endif // RESIZEPHOTO_H

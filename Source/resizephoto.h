#ifndef RESIZEPHOTO_H
#define RESIZEPHOTO_H

#include <QDialog>
#include <QAbstractButton>

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

    void on_ResizeButtonBox_accepted();

    void on_ResizeButtonBox_rejected();

private:
    Ui::resizephoto *ui;

    int wvt,hvt;

};

#endif // RESIZEPHOTO_H

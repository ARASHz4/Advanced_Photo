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

    static void setRsWidth(int value);
    static int RsWidth();

    static void setRsHeight(int value);
    static int RsHeight();

    static void setRekar(bool value);
    static bool Rekar();

    static void setResz(bool value);
    static bool Resz();

private:
    Ui::resizephoto *ui;

    static int rsWidth, rsHeight;
    static bool rekar, resz;

    int w, h, tw, th, wvt, hvt;
    bool wc, hc;
    QPixmap pres;
    QPushButton OK, Cancel;

private slots:
    void show();

    void on_Width_valueChanged();

    void on_Height_valueChanged();

    void SetValue();

    void OKButton();

    void CancelButton();
};

#endif // RESIZEPHOTO_H

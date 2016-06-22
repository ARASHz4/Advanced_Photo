#ifndef RESIZEPHOTO_H
#define RESIZEPHOTO_H

#include <QDialog>
#include <QPushButton>
#include <QStringList>
#include <QPixmap>

namespace Ui {
class ResizePhoto;
}

class ResizePhoto : public QDialog
{
    Q_OBJECT

public:
    explicit ResizePhoto(QWidget *parent = 0);
    ~ResizePhoto();

    static void setRsWidth(int value);
    static int RsWidth();

    static void setRsHeight(int value);
    static int RsHeight();

    static void setRekar(bool value);
    static bool Rekar();

    static void setResz(bool value);
    static bool Resz();

private:
    Ui::ResizePhoto *ui;

    static int rsWidth, rsHeight;
    static bool rekar, resz;

    int w, h, tw, th, wvt, hvt;
    bool wc, hc;
    QPixmap pres;
    QPushButton OK, Cancel;

private slots:
    void Start();

    void on_Width_valueChanged();

    void on_Height_valueChanged();

    void SetValue();

    void OKButton();

    void CancelButton();
};

#endif // RESIZEPHOTO_H

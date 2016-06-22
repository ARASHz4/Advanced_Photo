#ifndef PHOTOINFO_H
#define PHOTOINFO_H

#include <QDialog>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QDateTime>

namespace Ui {
class PhotoInfo;
}

class PhotoInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoInfo(QWidget *parent = 0);
    ~PhotoInfo();

private slots:
    void Start();

    void on_OkButton_clicked();

private:
    Ui::PhotoInfo *ui;
};

#endif // PHOTOINFO_H

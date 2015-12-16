#include "goto.h"
#include "ui_goto.h"

extern QStringList PhotoAddress;
extern int ps;

GoTo::GoTo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoTo)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

GoTo::~GoTo()
{
    delete ui;
}

void GoTo::showEvent(QShowEvent *)
{
    ui->GoToSpinBox->setMaximum(PhotoAddress.count());
    ui->GoToSpinBox->setValue(ps+1);
}

void GoTo::on_GoPushButton_clicked()
{
    ps=ui->GoToSpinBox->value()-1;
    close();
}

void GoTo::on_CancelPushButton_clicked()
{
    close();
}

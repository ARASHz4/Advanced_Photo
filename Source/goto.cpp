#include "goto.h"
#include "ui_goto.h"

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
    extern QStringList PhotoAddress;
    extern int ps;

    Go.connect(&Go, SIGNAL(clicked()), this, SLOT(GoButton()));
    Cancel.connect(&Cancel, SIGNAL(clicked()), this, SLOT(CancelButton()));
    Go.setText(tr("Go"));
    Cancel.setText(tr("Cancel"));
    Go.setDefault(true);

    ui->GoToButtonBox->addButton(&Go, QDialogButtonBox::AcceptRole);
    ui->GoToButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);

    ui->GoToSpinBox->setMaximum(PhotoAddress.count());
    ui->GoToSpinBox->setValue(ps+1);
}

void GoTo::GoButton()
{
    extern int ps;

    ps=ui->GoToSpinBox->value()-1;
    close();
}

void GoTo::CancelButton()
{
    close();
}

#include "goto.h"
#include "ui_goto.h"
#include "photowindow.h"

GoTo::GoTo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoTo)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Start();
}

GoTo::~GoTo()
{
    delete ui;
}

void GoTo::Start()
{
    Go.connect(&Go, SIGNAL(clicked()), this, SLOT(GoButton()));
    Cancel.connect(&Cancel, SIGNAL(clicked()), this, SLOT(CancelButton()));
    Go.setText(tr("Go"));
    Cancel.setText(tr("Cancel"));
    Go.setDefault(true);

    ui->GoToButtonBox->addButton(&Go, QDialogButtonBox::AcceptRole);
    ui->GoToButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);

    ui->GoToSpinBox->setMaximum(PhotoWindow::PhotoAddress().count());
    ui->GoToSpinBox->setValue(PhotoWindow::Ps()+1);
}

void GoTo::GoButton()
{
    PhotoWindow::setPs(ui->GoToSpinBox->value()-1);
    close();
}

void GoTo::CancelButton()
{
    close();
}

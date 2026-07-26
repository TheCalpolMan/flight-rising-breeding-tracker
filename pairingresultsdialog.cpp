#include "pairingresultsdialog.h"
#include "ui_pairingresultsdialog.h"

PairingResultsDialog::PairingResultsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PairingResultsDialog)
{
    ui->setupUi(this);
}

PairingResultsDialog::~PairingResultsDialog()
{
    delete ui;
}

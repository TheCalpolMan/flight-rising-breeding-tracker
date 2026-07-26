#ifndef PAIRINGRESULTSDIALOG_H
#define PAIRINGRESULTSDIALOG_H

#include <QDialog>

namespace Ui {
class PairingResultsDialog;
}

class PairingResultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PairingResultsDialog(QWidget *parent = nullptr);
    ~PairingResultsDialog();

private:
    Ui::PairingResultsDialog *ui;
};

#endif // PAIRINGRESULTSDIALOG_H

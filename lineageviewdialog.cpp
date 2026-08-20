#include "lineageviewdialog.h"
#include "ui_lineageviewdialog.h"

LineageViewDialog::LineageViewDialog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LineageViewDialog)
{
    ui->setupUi(this);

    graphWidget = new LineageGraphWidget();
    setCentralWidget(graphWidget);
}

LineageViewDialog::~LineageViewDialog()
{
    delete ui;
}

void LineageViewDialog::setGraph(const std::vector<std::shared_ptr<Dragon> > dragons)
{
    graphWidget->setGraph(dragons);
}

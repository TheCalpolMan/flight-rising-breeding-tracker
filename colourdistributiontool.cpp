#include "colourdistributiontool.h"
#include "ui_colourdistributiontool.h"

#include <qframe.h>
#include <qgridlayout.h>
#include <qradiobutton.h>

ColourDistributionTool::ColourDistributionTool(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ColourDistributionTool)
{
    ui->setupUi(this);
}

ColourDistributionTool::~ColourDistributionTool()
{
    delete ui;
}

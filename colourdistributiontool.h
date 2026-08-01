#ifndef COLOURDISTRIBUTIONTOOL_H
#define COLOURDISTRIBUTIONTOOL_H

#include <QDialog>

namespace Ui {
class ColourDistributionTool;
}

class ColourDistributionTool : public QDialog
{
    Q_OBJECT

public:
    explicit ColourDistributionTool(QWidget *parent = nullptr);
    ~ColourDistributionTool();

private:
    Ui::ColourDistributionTool *ui;
};

#endif // COLOURDISTRIBUTIONTOOL_H

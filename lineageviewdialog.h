#ifndef LINEAGEVIEWDIALOG_H
#define LINEAGEVIEWDIALOG_H

#include <QMainWindow>

#include <QPointer>

#include "lineagegraphwidget.h"

namespace Ui {
class LineageViewDialog;
}

class LineageViewDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit LineageViewDialog(QWidget *parent = nullptr);
    ~LineageViewDialog();

    void setGraph(const std::vector<std::shared_ptr<Dragon>> dragons);

private:
    Ui::LineageViewDialog *ui;

    QPointer<LineageGraphWidget> graphWidget;
};

#endif // LINEAGEVIEWDIALOG_H

#ifndef COLOURDISTRIBUTIONTOOL_H
#define COLOURDISTRIBUTIONTOOL_H

#include <QDialog>

#include <memory>
#include <QScrollArea>
#include <QGraphicsScene>

#include "dragon.h"

namespace Ui {
class ColourDistributionTool;
}

class ColourDistributionTool : public QDialog
{
    Q_OBJECT

public:
    explicit ColourDistributionTool(QWidget *parent = nullptr);
    ~ColourDistributionTool();

    void open(const Dragon& dragon, const std::vector<std::shared_ptr<Dragon>>& possibleParentDragons);
    
    void updateDisplay(const Dragon& dragon, const std::vector<std::shared_ptr<Dragon> > &possibleParentDragons);

private slots:
    void on_recentreprimarypushButton_clicked();

    void on_recentresecondarypushButton_clicked();

    void on_recentretertiarypushButton_clicked();

private:
    Ui::ColourDistributionTool *ui;

    std::vector<std::shared_ptr<QGraphicsScene>> primaryColourViews = decltype(primaryColourViews)();
    std::vector<std::shared_ptr<QGraphicsScene>> secondaryColourViews = decltype(secondaryColourViews)();
    std::vector<std::shared_ptr<QGraphicsScene>> tertiaryColourViews = decltype(tertiaryColourViews)();

    static void scrollToMiddle(QScrollArea* scrollArea);

    static std::vector<std::shared_ptr<QGraphicsScene>> createAllColourViewFrames(QWidget* parentWidget, const std::string& prefix);

    static void populateDragons(QWidget* scrollAreaWidgetContents, int geneColour, int colourOffset, const std::vector<std::shared_ptr<Dragon>>& possibleParentDragons);

    static void setMiddleColour(QWidget* scrollAreaWidgetContents, const std::vector<std::shared_ptr<QGraphicsScene>>& graphicsSenes, int index);
};

#endif // COLOURDISTRIBUTIONTOOL_H

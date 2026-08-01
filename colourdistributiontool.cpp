#include "colourdistributiontool.h"
#include "ui_colourdistributiontool.h"

#include <QLabel>
#include <QFrame>
#include <QScrollBar>
#include <QGridLayout>
#include <QRadioButton>
#include <QGraphicsView>
#include <QAbstractSlider>

#include "information.h"

ColourDistributionTool::ColourDistributionTool(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ColourDistributionTool)
{
    ui->setupUi(this);

    ui->primaryscrollAreaWidgetContents = new QWidget();
    primaryColourViews = createAllColourViewFrames(ui->primaryscrollAreaWidgetContents, "primary");
    ui->primaryscrollArea->setWidget(ui->primaryscrollAreaWidgetContents);

    ui->secondaryscrollAreaWidgetContents = new QWidget();
    secondaryColourViews = createAllColourViewFrames(ui->secondaryscrollAreaWidgetContents, "secondary");
    ui->secondaryscrollArea->setWidget(ui->secondaryscrollAreaWidgetContents);

    ui->tertiaryscrollAreaWidgetContents = new QWidget();
    tertiaryColourViews = createAllColourViewFrames(ui->tertiaryscrollAreaWidgetContents, "tertiary");
    ui->tertiaryscrollArea->setWidget(ui->tertiaryscrollAreaWidgetContents);
}

ColourDistributionTool::~ColourDistributionTool()
{
    delete ui;
}

void ColourDistributionTool::open(const Dragon &dragon, const std::vector<Dragon> &possibleParentDragons)
{
    updateDisplay(dragon, possibleParentDragons);

    show();

    scrollToMiddle(ui->primaryscrollArea);
    scrollToMiddle(ui->secondaryscrollArea);
    scrollToMiddle(ui->tertiaryscrollArea);
}

void ColourDistributionTool::updateDisplay(const Dragon &dragon, const std::vector<Dragon> &possibleParentDragons)
{
    setMiddleColour(ui->primaryscrollAreaWidgetContents, primaryColourViews, dragon.primaryColour.wheelIndex);
    setMiddleColour(ui->secondaryscrollAreaWidgetContents, secondaryColourViews, dragon.secondaryColour.wheelIndex);
    setMiddleColour(ui->tertiaryscrollAreaWidgetContents, tertiaryColourViews, dragon.tertiaryColour.wheelIndex);

    populateDragons(ui->primaryscrollAreaWidgetContents, 1, dragon.primaryColour.wheelIndex, possibleParentDragons);
    populateDragons(ui->secondaryscrollAreaWidgetContents, 2, dragon.secondaryColour.wheelIndex, possibleParentDragons);
    populateDragons(ui->tertiaryscrollAreaWidgetContents, 3, dragon.tertiaryColour.wheelIndex, possibleParentDragons);
}

void ColourDistributionTool::scrollToMiddle(QScrollArea *scrollArea)
{
    QScrollBar* scrollBar = scrollArea->verticalScrollBar();
    scrollBar->setValue((scrollBar->minimum() + scrollBar->maximum()) / 2);
}

std::vector<std::shared_ptr<QGraphicsScene>> ColourDistributionTool::createAllColourViewFrames(QWidget *parentWidget, const std::string &prefix)
{
    std::vector<std::shared_ptr<QGraphicsScene>> graphicsViews = decltype(graphicsViews)();

    QGridLayout* gridLayout = new QGridLayout(parentWidget);
    gridLayout->setObjectName(prefix + "GridLayout");
    gridLayout->setVerticalSpacing(2);

    for (int i = 0; i < 177; i++)
    {
        graphicsViews.push_back(std::make_shared<QGraphicsScene>());
        std::string indexString = std::to_string(i);

        while (indexString.size() < 3)
        {
            indexString = "0" + indexString;
        }

        QFrame* frame = new QFrame(parentWidget);
        frame->setObjectName(prefix + "colourViewFrame_" + indexString);
        frame->setMinimumSize(QSize(0, 20));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        QGraphicsView* graphicsView = new QGraphicsView(frame);
        graphicsView->setObjectName(prefix + "graphicsView_" + indexString);
        graphicsView->setGeometry(QRect(2, 2, 16, 16));

        QLabel* colourNameLabel = new QLabel(frame);
        colourNameLabel->setObjectName(prefix + "colourNameLabel_" + indexString);
        colourNameLabel->setGeometry(QRect(30, 0, 68, 20));

        QFrame* line = new QFrame(frame);
        line->setObjectName(prefix + "line_" + indexString);
        line->setGeometry(QRect(105, 2, 16, 16));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        QLabel* dragonLabel = new QLabel(frame);
        dragonLabel->setObjectName(prefix + "dragonLabel_" + indexString);
        dragonLabel->setGeometry(QRect(125, 0, 421, 20));

        gridLayout->addWidget(frame, i, 0, 1, 1);
    }

    return graphicsViews;
}

void ColourDistributionTool::populateDragons(QWidget *scrollAreaWidgetContents, int geneColour, int colourOffset, const std::vector<Dragon> &possibleParentDragons)
{
    auto frames = scrollAreaWidgetContents->findChildren<QFrame*>(Qt::FindDirectChildrenOnly);

    std::sort(frames.begin(), frames.end(),
        [](const QFrame* a, const QFrame* b){
            return a->objectName().toStdString() < b->objectName().toStdString();
        });

    for (auto frame : frames)
    {
        auto labelChildren = frame->findChildren<QLabel *>(Qt::FindDirectChildrenOnly);

        for (auto child : labelChildren)
        {
            if (!child->objectName().contains("dragonLabel_"))
            {
                continue;
            }

            child->setText("");
        }
    }

    for (const auto& dragon : possibleParentDragons)
    {
        Colour colour;

        switch(geneColour)
        {
        case 1: colour = dragon.primaryColour;break;
        case 2: colour = dragon.secondaryColour;break;
        case 3: colour = dragon.tertiaryColour;break;
        default:throw std::invalid_argument("geneColour must be 1-3");
        }

        auto frame = frames.at((colour.wheelIndex - colourOffset + 177 / 2 + 177) % 177);
        auto labelChildren = frame->findChildren<QLabel *>(Qt::FindDirectChildrenOnly);

        for (auto child : labelChildren)
        {
            if (!child->objectName().contains("dragonLabel_"))
            {
                continue;
            }

            if (child->text() == "")
            {
                child->setText(dragon.name.c_str());
                continue;
            }

            child->setText((child->text().toStdString() + ", " + dragon.name).c_str());
        }
    }
}

void ColourDistributionTool::setMiddleColour(QWidget *scrollAreaWidgetContents, const std::vector<std::shared_ptr<QGraphicsScene> > &graphicsSenes, int index)
{
    auto frames = scrollAreaWidgetContents->findChildren<QFrame*>(Qt::FindDirectChildrenOnly);

    std::sort(frames.begin(), frames.end(),
        [](const QFrame* a, const QFrame* b){
            return a->objectName().toStdString() < b->objectName().toStdString();
        });

    auto colours = Information::getInstance().getColours(true);

    for (int i = 0; i < 177; i++)
    {
        Colour colour = colours.at((i + index + (colours.size() + 1) / 2) % colours.size());

        auto labelChildren = frames.at(i)->findChildren<QLabel *>(Qt::FindDirectChildrenOnly);

        for (auto child : labelChildren)
        {
            if (!child->objectName().contains("colourNameLabel_"))
            {
                continue;
            }

            if (i != 177 / 2)
            {
                child->setText(colour.name.c_str());
                continue;
            }

            child->setText(("<html><b>" + colour.name + "</b></html>").c_str());
        }

        auto graphicsView = frames.at(i)->findChild<QGraphicsView*>();

        auto brush = QBrush(QColor(QString(colour.hexCode.c_str())));
        graphicsSenes.at(i)->setBackgroundBrush(brush);
        graphicsView->setScene(&*graphicsSenes.at(i));
        graphicsView->show();
    }
}

void ColourDistributionTool::on_recentreprimarypushButton_clicked()
{
    scrollToMiddle(ui->primaryscrollArea);
}


void ColourDistributionTool::on_recentresecondarypushButton_clicked()
{
    scrollToMiddle(ui->secondaryscrollArea);
}


void ColourDistributionTool::on_recentretertiarypushButton_clicked()
{
    scrollToMiddle(ui->tertiaryscrollArea);
}

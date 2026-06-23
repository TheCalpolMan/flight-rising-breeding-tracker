#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "information.h"

#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // getting relevant ui elements

    auto tab = ui->tabWidget->widget(0);
    auto frames = tab->findChildren<QFrame*>(Qt::FindDirectChildrenOnly);

    std::sort(frames.begin(), frames.end(),
        [](const QFrame* a, const QFrame* b){
            return a->objectName().toStdString() < b->objectName().toStdString();
        });

    for (int i = 0; i < frames.size(); i++)
    {
        if (!frames.at(i)->objectName().startsWith(QString("colourdisplayframe")))
        {
            continue;
        }

        colourViews.push_back(frames.at(i)->findChild<QGraphicsView *>());

        colourScenes.push_back(std::make_unique<QGraphicsScene>());
    }

    // assigning possible values to elements

    for (const auto& colour : Information::getInstance().getColours(true))
    {
        ui->primarycolourcombobox->addItem(QString(colour.name.c_str()));
        ui->secondarycolourcombobox->addItem(QString(colour.name.c_str()));
        ui->tertiarycolourcombobox->addItem(QString(colour.name.c_str()));
    }

    for (const auto& gene : Information::getInstance().getBreeds())
    {
        ui->breedcombobox->addItem(QString(gene.string.c_str()));
    }

    for (const auto& gene : Information::getInstance().getPrimaryGenes())
    {
        ui->primarygenecombobox->addItem(QString(gene.string.c_str()));
    }

    for (const auto& gene : Information::getInstance().getSecondaryGenes())
    {
        ui->secondarygenecombobox->addItem(QString(gene.string.c_str()));
    }

    for (const auto& gene : Information::getInstance().getTertiaryGenes())
    {
        ui->tertiarygenecombobox->addItem(QString(gene.string.c_str()));
    }

    for (const auto& gene : Information::getInstance().getEyes())
    {
        ui->eyecombobox->addItem(QString(gene.string.c_str()));
    }

    updateColours(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColoursBasedOnGene(bool showDialogOnNoColour)
{
    std::string colourString;

    switch (geneSelected)
    {
    case 0:
        colourString = ui->primarycolourcombobox->currentText().toStdString();
        break;
    case 1:
        colourString = ui->secondarycolourcombobox->currentText().toStdString();
        break;
    case 2:
        colourString = ui->tertiarycolourcombobox->currentText().toStdString();
        break;
    }

    auto colours = Information::getInstance().getColours(true);

    int colourIndex = -1;

    for (int i = 0; i < colours.size(); i++)
    {
        if (colours.at(i).name == colourString)
        {
            colourIndex = i;
            break;
        }
    }

    if (colourIndex == -1)
    {
        if (!showDialogOnNoColour)
        {
            return;
        }

        QMessageBox msgBox;
        msgBox.setText("Invalid colour in selected message box");
        msgBox.setDefaultButton(QMessageBox::Close);
        msgBox.exec();

        return;
    }

    updateColours(colourIndex);
}

void MainWindow::updateColours(int middleValue)
{
    int offset = (colourScenes.size() / 2 + 1 + middleValue) % colourScenes.size();

    for (int i=0; i < colourScenes.size(); i++)
    {
        auto brush = QBrush(QColor(
            QString(Information::getInstance().getColours(true).at(
                (i + offset) % Information::getInstance().getColours(true).size()).hexCode.c_str())));

        colourScenes.at(i)->setBackgroundBrush(brush);
        colourViews.at(i)->setScene(&*colourScenes.at(i));
        colourViews.at(i)->show();
    }
}

void MainWindow::on_primaryradiobutton_toggled(bool checked)
{
    if (checked)
    {
        geneSelected = 0;

        updateColoursBasedOnGene(true);
    }
}

void MainWindow::on_secondaryradiobutton_toggled(bool checked)
{
    if (checked)
    {
        geneSelected = 1;

        updateColoursBasedOnGene(true);
    }
}

void MainWindow::on_tertiaryradiobutton_toggled(bool checked)
{
    if (checked)
    {
        geneSelected = 2;

        updateColoursBasedOnGene(true);
    }
}

void MainWindow::on_primarycolourcombobox_currentTextChanged(const QString &text)
{
    updateColoursBasedOnGene(false);
}


void MainWindow::on_secondarycolourcombobox_currentTextChanged(const QString &text)
{
    updateColoursBasedOnGene(false);
}

void MainWindow::on_tertiarycolourcombobox_currentTextChanged(const QString &text)
{
    updateColoursBasedOnGene(false);
}


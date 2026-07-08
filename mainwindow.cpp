#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "information.h"

#include <QMessageBox>
#include <QFileDialog>

#include "dragon.h"
#include "urlopener.h"
#include "searchbuilder.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // inital setup

    ui->breedgraphicsview->setScene(&dragonScene);

    QPixmap pixmap("images/dragon-image-select.jpg");
    ui->breedgraphicsview->scene()->addPixmap(pixmap);

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

        colourLabels.push_back(frames.at(i)->findChild<QLabel *>());
        colourViews.push_back(frames.at(i)->findChild<QGraphicsView *>());

        colourScenes.push_back(std::make_shared<QGraphicsScene>());
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
    int offset = middleValue - colourScenes.size() / 2;
    auto colours = Information::getInstance().getColours(true);

    for (int i=0; i < colourScenes.size(); i++)
    {
        Colour colour = colours.at((i + offset + colours.size()) % colours.size());

        colourLabels.at(i)->setText(QString(colour.name.c_str()));

        auto brush = QBrush(QColor(QString(colour.hexCode.c_str())));
        colourScenes.at(i)->setBackgroundBrush(brush);
        colourViews.at(i)->setScene(&*colourScenes.at(i));
        colourViews.at(i)->show();
    }
}

void MainWindow::updateSearchColourLabel(QLabel* label, const std::string& name, QSlider* range, QSlider* offset)
{
    QString primaryColourStats = std::string("<html><head/><body><p><span style=\" font-weight:700;\">" + name + " colour range, offset:</span> " +
                                     std::to_string(range->value()) + ", " +
                                     std::to_string(offset->value() - offset->maximum() / 2) + "</p></body></html>").c_str();

    label->setText(primaryColourStats);
}

SaveFormat MainWindow::constructSave()
{
    SaveFormat format = SaveFormat(
        constructMorphologyDragon(),
        ui->primarygenecheckbox->isChecked(),
        ui->secondarygenecheckbox->isChecked(),
        ui->tertiarygenecheckbox->isChecked(),
        ui->breedcheckbox->isChecked(),
        ui->primarycolourrangeslider->value(),
        ui->primarycolouroffsetslider->value() - ui->primarycolouroffsetslider->maximum() / 2,
        ui->secondarycolourrangeslider->value(),
        ui->secondarycolouroffsetslider->value() - ui->secondarycolouroffsetslider->maximum() / 2,
        ui->tertiarycolourrangeslider->value(),
        ui->tertiarycolouroffsetslider->value() - ui->tertiarycolouroffsetslider->maximum() / 2
    );

    return format;
}

Dragon MainWindow::constructMorphologyDragon()
{
    const auto& information = Information::getInstance();

    Dragon dragon = Dragon(
        information.getEyes().at(ui->eyecombobox->currentIndex()),
        information.getBreeds().at(ui->breedcombobox->currentIndex()),
        information.getColours(true).at(ui->primarycolourcombobox->currentIndex()),
        information.getColours(true).at(ui->secondarycolourcombobox->currentIndex()),
        information.getColours(true).at(ui->tertiarycolourcombobox->currentIndex()),
        information.getPrimaryGenes().at(ui->primarygenecombobox->currentIndex()),
        information.getSecondaryGenes().at(ui->secondarygenecombobox->currentIndex()),
        information.getTertiaryGenes().at(ui->tertiarygenecombobox->currentIndex())
    );

    return dragon;
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


void MainWindow::on_breedgraphicsview_mousePressEvent(QMouseEvent *)
{
    // thanks to https://svenssonjoel.github.io/pages/qt_game_loadimage/index.html

    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Load Image"),
                                                    ".",
                                                    tr("Images (*.png *.jpg)"));

    if (filename.isEmpty())
    {
        return;
    }

    ui->breedgraphicsview->scene()->clear();

    QPixmap pixmap(filename);

    ui->breedgraphicsview->scene()->addPixmap(
        pixmap.scaled(ui->breedgraphicsview->size().shrunkBy(
            QMargins(1, 1, 1, 1)), Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_clicked()
{
    auto save = constructSave();

    Gender gender;

    switch(ui->gendercheckbox->checkState())
    {
    case Qt::PartiallyChecked: gender = Gender::Female;break;
    case Qt::Checked: gender = Gender::Male;break;
    default: gender = Gender::Any;break;
    }

    Currency currency;

    switch(ui->currencycheckbox->checkState())
    {
    case Qt::Checked: currency = Currency::Treasure;break;
    case Qt::PartiallyChecked: currency = Currency::Gems;break;
    default: currency = Currency::Any;break;
    }

    save.write("./test");

    UrlOpener::openUrl(SearchBuilder::fromSaveFormat(
        save,
        gender,
        currency
    ));
}

void MainWindow::on_primarycolouroffsetslider_valueChanged(int value)
{
    updateSearchColourLabel(ui->primarycoloursearchlabel, "Primary", ui->primarycolourrangeslider, ui->primarycolouroffsetslider);
}

void MainWindow::on_primarycolourrangeslider_valueChanged(int value)
{
    updateSearchColourLabel(ui->primarycoloursearchlabel, "Primary", ui->primarycolourrangeslider, ui->primarycolouroffsetslider);
}


void MainWindow::on_secondarycolourrangeslider_valueChanged(int value)
{
    updateSearchColourLabel(ui->secondarycoloursearchlabel, "Secondary", ui->secondarycolourrangeslider, ui->secondarycolouroffsetslider);
}


void MainWindow::on_secondarycolouroffsetslider_valueChanged(int value)
{
    updateSearchColourLabel(ui->secondarycoloursearchlabel, "Secondary", ui->secondarycolourrangeslider, ui->secondarycolouroffsetslider);
}


void MainWindow::on_tertiarycolourrangeslider_valueChanged(int value)
{
    updateSearchColourLabel(ui->tertiarycoloursearchlabel, "Tertiary", ui->tertiarycolourrangeslider, ui->tertiarycolouroffsetslider);
}


void MainWindow::on_tertiarycolouroffsetslider_valueChanged(int value)
{
    updateSearchColourLabel(ui->tertiarycoloursearchlabel, "Tertiary", ui->tertiarycolourrangeslider, ui->tertiarycolouroffsetslider);
}


void MainWindow::on_gendercheckbox_stateChanged(int arg1)
{
    ui->gendercheckbox->setText(QString(genderButtonStrings.at(arg1).c_str()));
}


void MainWindow::on_currencycheckbox_stateChanged(int arg1)
{
    ui->currencycheckbox->setText(QString(currencyButtonStrings.at(arg1).c_str()));
}


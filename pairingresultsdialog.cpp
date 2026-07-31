#include "pairingresultsdialog.h"
#include "ui_pairingresultsdialog.h"

#include <QList>
#include <iomanip>
#include <QVariant>

#include "information.h"
#include "vectorhelpers.h"

PairingResultsDialog::PairingResultsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PairingResultsDialog)
{
    ui->setupUi(this);

    boldFont.setBold(true);

    ui->treeWidget->setColumnWidth(0, ui->treeWidget->columnWidth(0) * 1.5);
}

PairingResultsDialog::~PairingResultsDialog()
{
    delete ui;
}

void PairingResultsDialog::enterResults(const std::multiset<BreedingTreeConfig> &results, const Dragon &dragon)
{
    ui->treeWidget->clear();
    treeItems.clear();

    this->dragon = dragon;
    dragonIndexes = DragonIndexes(dragon);

    int i = 0;
    for (auto it = results.rbegin(); it != results.rend() && i < 100; it++)
    {
        addResult(*it);
        i++;
    }

    ui->treeWidget->insertTopLevelItems(0, treeItems);
    ui->treeWidget->update();
}

void PairingResultsDialog::updatePercentage(int value)
{
    ui->progressBar->setValue(value);
}

bool PairingResultsDialog::probabilityCmp(const std::pair<int, double> &kvPair1, const std::pair<int, double> &kvPair2)
{
    return kvPair1.second > kvPair2.second;
}

std::multiset<std::pair<int, double>, std::function<bool (const std::pair<int, double> &, const std::pair<int, double> &)>>
    PairingResultsDialog::getSortedProbabilities(const std::unordered_map<int, double> &target)
{
    std::multiset<std::pair<int, double>, std::function<bool (const std::pair<int, double> &, const std::pair<int, double> &)>> sorted = decltype(sorted)(probabilityCmp);

    sorted.insert(target.cbegin(), target.cend());

    return sorted;
}

std::multiset<std::pair<int, double>, std::function<bool (const std::pair<int, double> &, const std::pair<int, double> &)> > PairingResultsDialog::getSortedColourProbabilities(const double target[])
{
    std::multiset<std::pair<int, double>, std::function<bool (const std::pair<int, double> &, const std::pair<int, double> &)>> sorted = decltype(sorted)(probabilityCmp);

    for (int i = 0; i < 177; i++)
    {
        if (target[i] == 0)
        {
            continue;
        }

        sorted.emplace(i, target[i]);
    }

    return sorted;
}

void PairingResultsDialog::addGeneColumn(QTreeWidgetItem &targetItem, int columnIndex, const std::unordered_map<int, double> &values, int targetGeneIndex, const std::vector<Allele> &genes)
{
    auto sorted = getSortedProbabilities(values);

    targetItem.setData(columnIndex, Qt::DisplayRole, QVariant(QString((
        genes.at(sorted.begin()->first).string + " " + getChanceAsString(sorted.begin()->second * 100) + "%"
    ).c_str())));

    if (sorted.begin()->first == targetGeneIndex)
    {
        targetItem.setFont(columnIndex, boldFont);
    }

    std::stringstream tooltip;
    tooltip << "<html>";

    int i = 0;
    for(auto it = sorted.cbegin(); it != sorted.cend() && i < 12; it++)
    {
        if (it->first == targetGeneIndex)
        {
            tooltip << "<b>";
        }

        tooltip << genes.at(it->first).string + " " + getChanceAsString(it->second * 100) + "%";

        if (it->first == targetGeneIndex)
        {
            tooltip << "</b>";
        }

        i++;

        if (i < sorted.size())
        {
            tooltip << "<br>";
        }
    }

    if (i == 12)
    {
        tooltip << "...";
    }

    tooltip << "</html>";

    targetItem.setToolTip(columnIndex, QString(tooltip.str().c_str()));
}

void PairingResultsDialog::addColourColumn(QTreeWidgetItem &targetItem, int columnIndex, const double values[], int targetColourIndex)
{
    auto& colours = Information::getInstance().getColours(true);
    auto sorted = getSortedColourProbabilities(values);

    targetItem.setData(columnIndex, Qt::DisplayRole, QVariant(QString((
        colours.at(sorted.begin()->first).name + " " + getChanceAsString(sorted.begin()->second * 100) + "%"
    ).c_str())));

    if (sorted.begin()->first == targetColourIndex)
    {
        targetItem.setFont(columnIndex, boldFont);
    }

    std::stringstream tooltip;
    tooltip << "<html>";

    int i = 0;
    for(auto it = sorted.cbegin(); it != sorted.cend() && i < 12; it++)
    {
        if (it->first == targetColourIndex)
        {
            tooltip << "<b>";
        }

        tooltip << colours.at(it->first).name + " " + getChanceAsString(it->second * 100) + "%";

        if (it->first == targetColourIndex)
        {
            tooltip << "</b>";
        }

        i++;

        if (i < sorted.size())
        {
            tooltip << "<br>";
        }
    }

    if (i == 12)
    {
        tooltip << "...";
    }

    tooltip << "</html>";

    targetItem.setToolTip(columnIndex, QString(tooltip.str().c_str()));
}

std::string PairingResultsDialog::getChanceAsString(double chance)
{
    std::stringstream stream;

    stream << std::fixed << std::setprecision(5) << chance;

    return stream.str();
}

void PairingResultsDialog::addResult(const BreedingTreeConfig &result)
{
    std::string title = getChanceAsString(result.getCalculatedChance() * 100) + "%";
    addChildResult(nullptr, result.treeRoot, title);
}

void PairingResultsDialog::addChildResult(QTreeWidgetItem *parent, std::shared_ptr<BinaryTreePossibilityNode> childResult, std::string title)
{
    auto& information = Information::getInstance();

    auto resultRow = treeItems.emplace_back(new QTreeWidgetItem());

    resultRow->setData(0, Qt::DisplayRole, QVariant(title.c_str()));

    addGeneColumn(*resultRow, 1, childResult->possibility->breed, dragonIndexes.breed, information.getBreeds());

    addColourColumn(*resultRow, 2, childResult->possibility->primaryColour, dragonIndexes.primaryColour);
    addColourColumn(*resultRow, 3, childResult->possibility->secondaryColour, dragonIndexes.secondaryColour);
    addColourColumn(*resultRow, 4, childResult->possibility->tertiaryColour, dragonIndexes.tertiaryColour);

    addGeneColumn(*resultRow, 5, childResult->possibility->primaryGene, dragonIndexes.primaryGene, information.getPrimaryGenes());
    addGeneColumn(*resultRow, 6, childResult->possibility->secondaryGene, dragonIndexes.secondaryGene, information.getSecondaryGenes());
    addGeneColumn(*resultRow, 7, childResult->possibility->tertiaryGene, dragonIndexes.tertiaryGene, information.getTertiaryGenes());

    if (parent != nullptr)
    {
        parent->addChild(resultRow);
    }

    if (childResult->isLeaf())
    {
        return;
    }

    addChildResult(resultRow, childResult->castLeft(), childResult->castLeft()->possibility->name);
    addChildResult(resultRow, childResult->castRight(), childResult->castRight()->possibility->name);
}

PairingResultsDialog::DragonIndexes::DragonIndexes(const Dragon &dragon)
{
    const auto& information = Information::getInstance();

    breed = VectorHelpers::getIndex(information.getBreeds(), dragon.breed);

    primaryColour = VectorHelpers::getIndex(information.getColours(true), dragon.primaryColour);
    secondaryColour = VectorHelpers::getIndex(information.getColours(true), dragon.secondaryColour);
    tertiaryColour = VectorHelpers::getIndex(information.getColours(true), dragon.tertiaryColour);

    primaryGene = VectorHelpers::getIndex(information.getPrimaryGenes(), dragon.primaryGene);
    secondaryGene = VectorHelpers::getIndex(information.getSecondaryGenes(), dragon.secondaryGene);
    tertiaryGene = VectorHelpers::getIndex(information.getTertiaryGenes(), dragon.tertiaryGene);
}

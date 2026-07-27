#include "pairingresultsdialog.h"
#include "ui_pairingresultsdialog.h"

#include <QList>
#include <QVariant>

#include "information.h"

PairingResultsDialog::PairingResultsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PairingResultsDialog)
{
    ui->setupUi(this);
}

PairingResultsDialog::~PairingResultsDialog()
{
    delete ui;
}

void PairingResultsDialog::enterResults(const std::multiset<BreedingTreeConfig> &results)
{
    ui->treeWidget->clear();
    treeItems.clear();

    int i = 0;
    for (auto it = results.rbegin(); it != results.rend() && i < 100; it++)
    {
        addResult(*it);
        i++;
    }

    ui->treeWidget->insertTopLevelItems(0, treeItems);
    ui->treeWidget->update();
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

void PairingResultsDialog::addGeneColumn(QTreeWidgetItem &targetItem, int columnIndex, const std::unordered_map<int, double> &values, const std::vector<Allele> &genes)
{
    auto sorted = getSortedProbabilities(values);

    targetItem.setData(columnIndex, Qt::DisplayRole, QVariant(QString((
        genes.at(sorted.begin()->first).string + " " + std::to_string(sorted.begin()->second * 100) + "%"
    ).c_str())));

    std::stringstream tooltip;

    int i = 0;
    for(auto it = sorted.cbegin(); it != sorted.cend() && i < 12; it++)
    {
        tooltip << genes.at(it->first).string + " " + std::to_string(it->second * 100) + "%";

        i++;

        if (i < sorted.size())
        {
            tooltip << std::endl;
        }
    }

    if (i == 12)
    {
        tooltip << "...";
    }

    targetItem.setToolTip(columnIndex, QString(tooltip.str().c_str()));
}

void PairingResultsDialog::addColourColumn(QTreeWidgetItem &targetItem, int columnIndex, const std::unordered_map<int, double> &values)
{
    auto& colours = Information::getInstance().getColours(true);
    auto sorted = getSortedProbabilities(values);

    targetItem.setData(columnIndex, Qt::DisplayRole, QVariant(QString((
        colours.at(sorted.begin()->first).name + " " + std::to_string(sorted.begin()->second * 100) + "%"
    ).c_str())));

    std::stringstream tooltip;

    int i = 0;
    for(auto it = sorted.cbegin(); it != sorted.cend() && i < 12; it++)
    {
        tooltip << colours.at(it->first).name + " " + std::to_string(it->second * 100) + "%";

        i++;

        if (i < sorted.size())
        {
            tooltip << std::endl;
        }
    }

    if (i == 12)
    {
        tooltip << "...";
    }

    targetItem.setToolTip(columnIndex, QString(tooltip.str().c_str()));
}

void PairingResultsDialog::addResult(const BreedingTreeConfig &result)
{
    std::string title = std::to_string(result.getCalculatedChance() * 100) + "%";
    addChildResult(nullptr, result.treeRoot, title);
}

void PairingResultsDialog::addChildResult(QTreeWidgetItem *parent, std::shared_ptr<BinaryTreePossibilityNode> childResult, std::string title)
{
    auto& information = Information::getInstance();

    auto resultRow = treeItems.emplace_back(new QTreeWidgetItem());

    resultRow->setData(0, Qt::DisplayRole, QVariant(title.c_str()));
    addGeneColumn(*resultRow, 1, childResult->possibility->breed, information.getBreeds());

    addColourColumn(*resultRow, 2, childResult->possibility->primaryColour);
    addColourColumn(*resultRow, 3, childResult->possibility->secondaryColour);
    addColourColumn(*resultRow, 4, childResult->possibility->tertiaryColour);

    addGeneColumn(*resultRow, 5, childResult->possibility->primaryGene, information.getPrimaryGenes());
    addGeneColumn(*resultRow, 6, childResult->possibility->secondaryGene, information.getSecondaryGenes());
    addGeneColumn(*resultRow, 7, childResult->possibility->tertiaryGene, information.getTertiaryGenes());

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

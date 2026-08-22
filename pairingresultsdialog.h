#ifndef PAIRINGRESULTSDIALOG_H
#define PAIRINGRESULTSDIALOG_H

#include <QDialog>

#include <set>
#include <functional>
#include <QTreeWidgetItem>

#include "dragon.h"
#include "breedingtreeconfig.h"

namespace Ui {
class PairingResultsDialog;
}

class PairingResultsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PairingResultsDialog(QWidget *parent = nullptr);
    ~PairingResultsDialog();

public slots:

    void updatePercentage(int value);

    void enterResults(const std::multiset<BreedingTreeConfig>& results, const Dragon& dragon);

private slots:
    void on_sortingComboBox_currentIndexChanged(int index);

private:
    struct DragonIndexes
    {
        DragonIndexes() = default;

        DragonIndexes(const Dragon& dragon);

        int breed;

        int primaryColour;
        int secondaryColour;
        int tertiaryColour;

        int primaryGene;
        int secondaryGene;
        int tertiaryGene;
    };

    static std::string getChanceAsString(double chance);

    static bool probabilityCmp(const std::pair<int, double>& kvPair1, const std::pair<int, double>& kvPair2);

    static bool percentageCmp(const BreedingTreeConfig& config1, const BreedingTreeConfig& config2);

    static bool branchPercentageCmp(const BreedingTreeConfig& config1, const BreedingTreeConfig& config2);

    static bool generationPercentageCmp(const BreedingTreeConfig& config1, const BreedingTreeConfig& config2);

    static std::multiset<std::pair<int, double>, std::function<bool(const std::pair<int, double>&, const std::pair<int, double>&)>>
        getSortedProbabilities(const std::unordered_map<int, double>& target);

    static std::multiset<std::pair<int, double>, std::function<bool(const std::pair<int, double>&, const std::pair<int, double>&)>>
        getSortedColourProbabilities(const double target[]);

    void addGeneColumn(QTreeWidgetItem& targetItem, int columnIndex, const std::unordered_map<int, double> &values, int targetGeneIndex, const std::vector<Allele>& genes);

    void addColourColumn(QTreeWidgetItem& targetItem, int columnIndex, const double values[], int targetColourIndex);

    void addResult(const BreedingTreeConfig& result);

    void addChildResult(QTreeWidgetItem* parent, std::shared_ptr<BinaryTreePossibilityNode> childResult, std::string title = "");

    void populateTree(const std::vector<BreedingTreeConfig>& resultSubset);

    Ui::PairingResultsDialog *ui;

    Dragon dragon;
    DragonIndexes dragonIndexes;
    std::vector<BreedingTreeConfig> results = decltype(results)();

    QFont boldFont;
    QList<QTreeWidgetItem*> treeItems = decltype(treeItems)();
};

#endif // PAIRINGRESULTSDIALOG_H

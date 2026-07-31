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

    static bool probabilityCmp(const std::pair<int, double>& kvPair1, const std::pair<int, double>& kvPair2);

    static std::multiset<std::pair<int, double>, std::function<bool(const std::pair<int, double>&, const std::pair<int, double>&)>>
        getSortedProbabilities(const std::unordered_map<int, double>& target);

    static std::multiset<std::pair<int, double>, std::function<bool(const std::pair<int, double>&, const std::pair<int, double>&)>>
        getSortedColourProbabilities(const double target[]);

    void addGeneColumn(QTreeWidgetItem& targetItem, int columnIndex, const std::unordered_map<int, double> &values, int targetGeneIndex, const std::vector<Allele>& genes);

    void addColourColumn(QTreeWidgetItem& targetItem, int columnIndex, const double values[], int targetColourIndex);

    static std::string getChanceAsString(double chance);

    void addResult(const BreedingTreeConfig& result);

    void addChildResult(QTreeWidgetItem* parent, std::shared_ptr<BinaryTreePossibilityNode> childResult, std::string title = "");

    Ui::PairingResultsDialog *ui;

    Dragon dragon;

    DragonIndexes dragonIndexes;

    QFont boldFont;

    QList<QTreeWidgetItem*> treeItems = decltype(treeItems)();
};

#endif // PAIRINGRESULTSDIALOG_H

#ifndef PAIRINGRESULTSDIALOG_H
#define PAIRINGRESULTSDIALOG_H

#include <QDialog>

#include <set>
#include <functional>
#include <QTreeWidgetItem>

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

    void enterResults(const std::multiset<BreedingTreeConfig>& results);

private:
    static bool probabilityCmp(const std::pair<int, double>& kvPair1, const std::pair<int, double>& kvPair2);

    static std::multiset<std::pair<int, double>, std::function<bool(const std::pair<int, double>&, const std::pair<int, double>&)>>
        getSortedProbabilities(const std::unordered_map<int, double>& target);

    static void addGeneColumn(QTreeWidgetItem& targetItem, int columnIndex, const std::unordered_map<int, double> &values, const std::vector<Allele>& genes);

    static void addColourColumn(QTreeWidgetItem& targetItem, int columnIndex, const std::unordered_map<int, double> &values);

    void addResult(const BreedingTreeConfig& result);

    void addChildResult(QTreeWidgetItem* parent, std::shared_ptr<BinaryTreePossibilityNode> childResult, std::string title = "");

    Ui::PairingResultsDialog *ui;

    QList<QTreeWidgetItem*> treeItems = decltype(treeItems)();
};

#endif // PAIRINGRESULTSDIALOG_H

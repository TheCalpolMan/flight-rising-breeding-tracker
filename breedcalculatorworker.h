#ifndef BREEDCALCULATORWORKER_H
#define BREEDCALCULATORWORKER_H

#include <QObject>

#include <set>

#include "dragon.h"
#include "breedingtreeconfig.h"

class BreedCalculatorWorker : public QObject
{
    Q_OBJECT
public:
    explicit BreedCalculatorWorker(QObject *parent = nullptr);

    const std::multiset<BreedingTreeConfig> &getConfigs();
private:
    static int factorial(int n);

    static int nPr(int n, int r);

    static std::vector<std::shared_ptr<Dragon>> convertDragonsToSharedPtr(const std::vector<Dragon>& dragons);

    static bool doesConfigHaveValidPairings(const BreedingTreeConfig& config);

    std::vector<std::shared_ptr<Dragon>> getPossibleParentPermutationFromSeed(int count, int seed) const;

    std::multiset<BreedingTreeConfig> validTreeConfigs = decltype(validTreeConfigs)();
    std::vector<std::shared_ptr<Dragon>> possibleParents;
    std::shared_ptr<Dragon> aim;

public slots:
    void doWork(const std::multiset<BreedingTreeConfig> &parameter, std::vector<std::shared_ptr<Dragon>> possibleParents, std::shared_ptr<Dragon> aim);

signals:
    void resultReady(const std::multiset<BreedingTreeConfig> &);

    void progressUpdate(int percentage);

};

#endif // BREEDCALCULATORWORKER_H

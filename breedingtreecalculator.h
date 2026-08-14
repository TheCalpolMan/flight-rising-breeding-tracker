#ifndef BREEDINGTREECALCULATOR_H
#define BREEDINGTREECALCULATOR_H

#include <set>
#include <vector>
#include <memory>

#include "dragon.h"
#include "breedingtreeconfig.h"

class BreedingTreeCalculator
{
public:
    BreedingTreeCalculator(Dragon aim, const std::vector<std::shared_ptr<Dragon>>& possibleParents);

    const std::multiset<BreedingTreeConfig>& getConfigs();
private:
    static int factorial(int n);

    static int nPr(int n, int r);

    static bool doesConfigHaveValidPairings(const BreedingTreeConfig& config);

    std::vector<std::shared_ptr<Dragon>> getPossibleParentPermutationFromSeed(int count, int seed) const;

    std::multiset<BreedingTreeConfig> validTreeConfigs = decltype(validTreeConfigs)();
    const std::vector<std::shared_ptr<Dragon>> possibleParents;
    std::shared_ptr<Dragon> aim;
};

#endif // BREEDINGTREECALCULATOR_H

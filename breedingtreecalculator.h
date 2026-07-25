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
    BreedingTreeCalculator(const std::vector<Dragon>& possibleParents);

    const std::set<BreedingTreeConfig>& getConfigs();
private:
    static int factorial(int n);

    static std::vector<std::shared_ptr<Dragon>> convertDragonsToSharedPtr(const std::vector<Dragon>& dragons);

    static bool doesConfigHaveValidPairings(const BreedingTreeConfig& config);

    std::vector<std::vector<std::shared_ptr<Dragon>>> getPossibleParentPermutations() const;

    std::vector<std::shared_ptr<Dragon>> getPossibleParentPermutationFromSeed(int seed) const;

    std::set<BreedingTreeConfig> validTreeConfigs = decltype(validTreeConfigs)();
    const std::vector<std::shared_ptr<Dragon>> possibleParents;
};

#endif // BREEDINGTREECALCULATOR_H

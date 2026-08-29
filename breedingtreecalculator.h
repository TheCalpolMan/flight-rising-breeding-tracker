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
    static std::vector<std::function<bool(const Dragon& aim, std::shared_ptr<Dragon>)>> conditions;

    const std::shared_ptr<Dragon> aim;
    const std::vector<unsigned long long> possibleParentSets;
    const std::vector<std::shared_ptr<Dragon>> possibleParents;
    std::multiset<BreedingTreeConfig> validTreeConfigs = decltype(validTreeConfigs)();

    static int factorial(int n);

    static int nCr(int n, int r);

    static int nPr(int n, int r);

    static void incrementCombination(std::vector<unsigned int>& combination, int maxValue);

    static void incrementCombinationIndexesUpwards(std::vector<unsigned int>& combination, int startIndex);

    static bool doesConfigHaveInbreeding(const BreedingTreeConfig& config);

    static bool doesConfigHaveValidPairings(const BreedingTreeConfig& config);

    static std::vector<unsigned long long> getDragonSetVector(const Dragon &aim, const std::vector<std::shared_ptr<Dragon>>& possibleParents);

    void initialiseDragons();

    bool doesCombinationContainAllSets(const std::vector<unsigned int>& combination) const;

    std::vector<std::shared_ptr<Dragon>> getPossibleParentPermutationFromSeed(int count, int seed) const;

    std::vector<std::shared_ptr<Dragon>> getSeededCombinationPermutation(std::vector<unsigned int> combination, int seed) const;
};

#endif // BREEDINGTREECALCULATOR_H

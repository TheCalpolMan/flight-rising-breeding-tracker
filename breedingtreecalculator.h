#ifndef BREEDINGTREECALCULATOR_H
#define BREEDINGTREECALCULATOR_H

#include <set>
#include <vector>
#include <memory>

#include "dragon.h"
#include "binarytreenode.h"
#include "breedingtreeconfig.h"

class BreedingTreeCalculator
{
public:
    BreedingTreeCalculator(std::shared_ptr<Dragon> aim, const std::vector<Dragon>& possibleParents);

    const std::multiset<BreedingTreeConfig>& getConfigs();
private:
    static int factorial(int n);

    static int nPr(int n, int r);

    static std::vector<std::shared_ptr<Dragon>> convertDragonsToSharedPtr(const std::vector<Dragon>& dragons);

    static bool doesConfigHaveValidPairings(std::shared_ptr<BinaryTreeNode> treeRoot, std::vector<std::shared_ptr<Dragon>> permutation);

    std::vector<std::shared_ptr<Dragon>> getPossibleParentPermutationFromSeed(int count, int seed) const;

    std::multiset<BreedingTreeConfig> validTreeConfigs = decltype(validTreeConfigs)();
    const std::vector<std::shared_ptr<Dragon>> possibleParents;
    std::shared_ptr<Dragon> aim;
};

#endif // BREEDINGTREECALCULATOR_H

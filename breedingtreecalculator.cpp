#include "breedingtreecalculator.h"

#include <list>

BreedingTreeCalculator::BreedingTreeCalculator(const std::vector<Dragon>& possibleParents) :
    possibleParents(convertDragonsToSharedPtr(possibleParents))
{

}

const std::set<BreedingTreeConfig> &BreedingTreeCalculator::getConfigs()
{
    if (!validTreeConfigs.empty())
    {
        return validTreeConfigs;
    }

    std::vector<std::vector<std::shared_ptr<Dragon>>> parentPermutations = getPossibleParentPermutations();


}

int BreedingTreeCalculator::factorial(int n)
{
    int value = 1;

    for (int i = 2; i <= n; i++)
    {
        value *= i;
    }

    return value;
}

std::vector<std::shared_ptr<Dragon>> BreedingTreeCalculator::convertDragonsToSharedPtr(const std::vector<Dragon> &dragons)
{
    std::vector<std::shared_ptr<Dragon>> sharedDragons = decltype(sharedDragons)();

    for(const auto& dragon : dragons)
    {
        sharedDragons.push_back(std::make_shared<Dragon>(dragon));
    }

    return sharedDragons;
}

bool BreedingTreeCalculator::doesConfigHaveValidPairings(const BreedingTreeConfig &config)
{
    std::list<std::shared_ptr<BinaryTreeNode>> nodesToCheck = decltype(nodesToCheck)();
    nodesToCheck.push_back(config.treeRoot);

    int dragonIndex = 0;

    while(!nodesToCheck.empty())
    {
        std::shared_ptr<BinaryTreeNode> currentNode = nodesToCheck.front();
        nodesToCheck.pop_front();

        if (currentNode->leftChild->isLeaf() && currentNode->rightChild->isLeaf() &&
            config.dragons.at(dragonIndex++)->male == config.dragons.at(dragonIndex++)->male)
        {
            return false;
        }

        if (!currentNode->rightChild->isLeaf())
        {
            nodesToCheck.push_front(currentNode->rightChild);
        }

        if (!currentNode->leftChild->isLeaf())
        {
            nodesToCheck.push_front(currentNode->leftChild);
        }
    }

    return true;
}

std::vector<std::vector<std::shared_ptr<Dragon>>> BreedingTreeCalculator::getPossibleParentPermutations() const
{
    int permutationCount = factorial(possibleParents.size());
    std::vector<std::vector<std::shared_ptr<Dragon>>> parentPermutations = decltype(parentPermutations)();

    for (int i = 0; i < permutationCount; i++)
    {
        parentPermutations.push_back(getPossibleParentPermutationFromSeed(i));
    }

    return parentPermutations;
}

std::vector<std::shared_ptr<Dragon>> BreedingTreeCalculator::getPossibleParentPermutationFromSeed(int seed) const
{
    std::vector<int> availableIndexes = decltype(availableIndexes)();
    std::vector<std::shared_ptr<Dragon>> permutation = decltype(permutation)();

    for (int i = 0; i < possibleParents.size(); i++)
    {
        availableIndexes.push_back(i);
    }

    while(availableIndexes.size() > 0)
    {
        int index = seed % availableIndexes.size();
        seed = seed / availableIndexes.size();

        permutation.push_back(possibleParents.at(availableIndexes.at(index)));
        availableIndexes.erase(availableIndexes.cbegin() + index);
    }

    return permutation;
}

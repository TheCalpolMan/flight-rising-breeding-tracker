#include "breedingtreecalculator.h"

#include <list>
#include <cassert>
#include <iostream>

#include "binarytreegenerator.h"

BreedingTreeCalculator::BreedingTreeCalculator(std::shared_ptr<Dragon> aim, const std::vector<Dragon>& possibleParents) :
    possibleParents(convertDragonsToSharedPtr(possibleParents)),
    aim(aim)
{

}

const std::multiset<BreedingTreeConfig> &BreedingTreeCalculator::getConfigs()
{
    if (!validTreeConfigs.empty())
    {
        return validTreeConfigs;
    }

    auto& treeGenerator = BinaryTreeGenerator::getInstance();

    for (int parentCount = 2; parentCount <= possibleParents.size(); parentCount++)
    {
        int permutationCount = nPr(possibleParents.size(), parentCount);

        for (int permutationSeed = 0; permutationSeed < permutationCount; permutationSeed++)
        {
            auto permutation = getPossibleParentPermutationFromSeed(parentCount, permutationSeed);

            // TODO remove
            for (const auto& dragon : permutation)
            {
                std::cout << dragon->name << ", ";
            }

            std::cout << std::endl;

            for (const auto& binaryTree : treeGenerator.getCombinations(parentCount))
            {
                if (!doesConfigHaveValidPairings(binaryTree, permutation))
                {
                    continue;
                }

                BreedingTreeConfig config = BreedingTreeConfig(aim, permutation, std::make_shared<BinaryTreePossibilityNode>(binaryTree, possibleParents));

                if (config.getChance() == 0)
                {
                    continue;
                }

                validTreeConfigs.insert(std::move(config));
            }
        }

        // TODO remove

        int x = 0;
        x++;
    }

    return validTreeConfigs;
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

int BreedingTreeCalculator::nPr(int n, int r)
{
    return factorial(n) / factorial(n - r);
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

bool BreedingTreeCalculator::doesConfigHaveValidPairings(std::shared_ptr<BinaryTreeNode> treeRoot, std::vector<std::shared_ptr<Dragon> > permutation)
{
    std::list<std::shared_ptr<BinaryTreeNode>> nodesToCheck = decltype(nodesToCheck)();
    nodesToCheck.push_back(treeRoot);

    int dragonIndex = 0;

    while(!nodesToCheck.empty())
    {
        std::shared_ptr<BinaryTreeNode> currentNode = nodesToCheck.front();
        nodesToCheck.pop_front();

        // forces males to always be on the left in double-leaf situations to rule out more duplicate permutations
        // also makes sure that in double-leaf situations we have a male & female breeding
        if (currentNode->leftChild->isLeaf() && currentNode->rightChild->isLeaf() &&
            (permutation.at(dragonIndex++)->male || permutation.at(dragonIndex++)->male))
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

std::vector<std::shared_ptr<Dragon>> BreedingTreeCalculator::getPossibleParentPermutationFromSeed(int count, int seed) const
{
    std::vector<int> availableIndexes = decltype(availableIndexes)();
    std::vector<std::shared_ptr<Dragon>> permutation = decltype(permutation)();

    for (int i = 0; i < possibleParents.size(); i++)
    {
        availableIndexes.push_back(i);
    }

    while(availableIndexes.size() > (possibleParents.size() - count))
    {
        int index = seed % availableIndexes.size();
        seed = seed / availableIndexes.size();

        permutation.push_back(possibleParents.at(availableIndexes.at(index)));
        availableIndexes.erase(availableIndexes.cbegin() + index);
    }

    return permutation;
}

#include "breedingtreecalculator.h"

#include <list>
#include <cassert>

#include "tracy/Tracy.hpp"

#include "modutils.h"
#include "information.h"
#include "binarytreegenerator.h"

BreedingTreeCalculator::BreedingTreeCalculator(Dragon aim, const std::vector<std::shared_ptr<Dragon>>& possibleParents) :
    aim(std::make_shared<Dragon>(aim)),
    possibleParents(possibleParents),
    possibleParentSets(getDragonSetVector(aim, possibleParents))
{

}

const std::multiset<BreedingTreeConfig> &BreedingTreeCalculator::getConfigs()
{
    ZoneScoped;

    initialiseDragons();

    if (!validTreeConfigs.empty())
    {
        return validTreeConfigs;
    }

    auto& treeGenerator = BinaryTreeGenerator::getInstance();

    int totalConfigs = 0;

    for (int parentCount = 2; parentCount <= possibleParents.size(); parentCount++)
    {
        totalConfigs += nPr(possibleParents.size(), parentCount) * treeGenerator.getCombinations(parentCount).size();
    }

    int configsDone = 0;

    for (int parentCount = 2; parentCount <= possibleParents.size(); parentCount++)
    {
        int combinationCount = nCr(possibleParents.size(), parentCount);

        std::vector<unsigned int> combination = decltype(combination)();

        for (int i = 0; i < parentCount; i++)
        {
            combination.push_back(i);
        }

        combination.back()--;

        for (int combinationSeed = 0; combinationSeed < combinationCount; combinationSeed++)
        {
            incrementCombination(combination, possibleParents.size());

            if (combination == std::vector<unsigned int>({1, 2, 5}))
            {
                int i = 0;
                i++;
            }

            if (!doesCombinationContainAllSets(combination))
            {
                continue;
            }

            int permutationCount = factorial(parentCount);

            for (int permutationSeed = 0; permutationSeed < permutationCount; permutationSeed++)
            {
                auto permutation = getSeededCombinationPermutation(combination, permutationSeed);

                for (const auto& binaryTree : treeGenerator.getCombinations(parentCount))
                {
                    BreedingTreeConfig config = BreedingTreeConfig(aim, permutation, std::make_shared<BinaryTreePossibilityNode>(binaryTree, permutation));
                    configsDone++;

                    if (!doesConfigHaveValidPairings(config))
                    {
                        continue;
                    }

                    if (doesConfigHaveInbreeding(config))
                    {
                        continue;
                    }

                    if (config.getChance() == 0)
                    {
                        continue;
                    }

                    validTreeConfigs.insert(std::move(config));
                }
            }
        }
    }

    return validTreeConfigs;
}

std::vector<std::function<bool (const Dragon &aim, std::shared_ptr<Dragon>)> > BreedingTreeCalculator::conditions =
{
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return dragon->male;},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return !dragon->male;},

    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return 0 <= ModUtils::getDisplacement(aim.primaryColour.wheelIndex, dragon->primaryColour.wheelIndex, Information::getInstance().getColours(true).size());},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return 0 >= ModUtils::getDisplacement(aim.primaryColour.wheelIndex, dragon->primaryColour.wheelIndex, Information::getInstance().getColours(true).size());},

    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return 0 <= ModUtils::getDisplacement(aim.secondaryColour.wheelIndex, dragon->secondaryColour.wheelIndex, Information::getInstance().getColours(true).size());},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return 0 >= ModUtils::getDisplacement(aim.secondaryColour.wheelIndex, dragon->secondaryColour.wheelIndex, Information::getInstance().getColours(true).size());},

    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return 0 <= ModUtils::getDisplacement(aim.tertiaryColour.wheelIndex, dragon->tertiaryColour.wheelIndex, Information::getInstance().getColours(true).size());},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return 0 >= ModUtils::getDisplacement(aim.tertiaryColour.wheelIndex, dragon->tertiaryColour.wheelIndex, Information::getInstance().getColours(true).size());},

    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return dragon->breed == aim.breed;},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return dragon->primaryGene == aim.primaryGene;},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return dragon->secondaryGene == aim.secondaryGene;},
    [](const Dragon& aim, std::shared_ptr<Dragon> dragon) {return dragon->tertiaryGene == aim.tertiaryGene;}
};

int BreedingTreeCalculator::factorial(int n)
{
    int value = 1;

    for (int i = 2; i <= n; i++)
    {
        value *= i;
    }

    return value;
}

int BreedingTreeCalculator::nCr(int n, int r)
{
    return factorial(n) / factorial(n - r) / factorial(r);
}

int BreedingTreeCalculator::nPr(int n, int r)
{
    return factorial(n) / factorial(n - r);
}

void BreedingTreeCalculator::incrementCombination(std::vector<unsigned int> &combination, int maxValue)
{
    for (int i = combination.size() - 1; i >= 0; i--)
    {
        int modulus = maxValue - combination.size() + i + 1;
        combination.at(i) = (combination.at(i) + 1) % modulus;

        if (combination.at(i) != 0)
        {
            incrementCombinationIndexesUpwards(combination, i + 1);
            return;
        }
    }
}

void BreedingTreeCalculator::incrementCombinationIndexesUpwards(std::vector<unsigned int> &combination, int startIndex)
{
    for (int i = startIndex; i < combination.size(); i++)
    {
        combination.at(i) = combination.at(i - 1) + 1;
    }
}

bool BreedingTreeCalculator::doesConfigHaveInbreeding(const BreedingTreeConfig &config)
{
    ZoneScoped;
    config.treeRoot->propogate();

    std::list<std::shared_ptr<BinaryTreePossibilityNode>> nodesToCheck = decltype(nodesToCheck)();
    nodesToCheck.push_back(config.treeRoot);

    while(!nodesToCheck.empty())
    {
        std::shared_ptr<BinaryTreePossibilityNode> currentNode = nodesToCheck.front();
        nodesToCheck.pop_front();

        if (currentNode->possibility->inbred)
        {
            return true;
        }

        if (!currentNode->rightChild->isLeaf())
        {
            nodesToCheck.push_front(currentNode->castRight());
        }

        if (!currentNode->leftChild->isLeaf())
        {
            nodesToCheck.push_front(currentNode->castLeft());
        }
    }

    return false;
}

bool BreedingTreeCalculator::doesConfigHaveValidPairings(const BreedingTreeConfig &config)
{
    ZoneScoped;

    std::list<std::shared_ptr<BinaryTreePossibilityNode>> nodesToCheck = decltype(nodesToCheck)();
    nodesToCheck.push_back(config.treeRoot);

    while(!nodesToCheck.empty())
    {
        std::shared_ptr<BinaryTreePossibilityNode> currentNode = nodesToCheck.front();
        nodesToCheck.pop_front();

        // forces males to always be on the left in double-leaf situations to rule out more duplicate permutations
        // also makes sure that in double-leaf situations we have a male & female breeding
        if (currentNode->leftChild->isLeaf() && currentNode->rightChild->isLeaf() &&
            (currentNode->castLeft()->possibility->gender != Gender::Male || currentNode->castRight()->possibility->gender != Gender::Female))
        {
            return false;
        }

        if (!currentNode->rightChild->isLeaf())
        {
            nodesToCheck.push_front(currentNode->castRight());
        }

        if (!currentNode->leftChild->isLeaf())
        {
            nodesToCheck.push_front(currentNode->castLeft());
        }
    }

    return true;
}

std::vector<unsigned long long> BreedingTreeCalculator::getDragonSetVector(const Dragon& aim, const std::vector<std::shared_ptr<Dragon> > &possibleParents)
{
    std::vector<unsigned long long> setVector = decltype(setVector)();

    for (const auto& parent : possibleParents)
    {
        unsigned long long dragonScore = 0b0;

        for (int i = 0; i < conditions.size(); i++)
        {
            if (conditions.at(i)(aim, parent))
            {
                dragonScore += 0b1 << i;
            }
        }

        setVector.push_back(dragonScore);
    }

    return setVector;
}

void BreedingTreeCalculator::initialiseDragons()
{
    for (int i = 0; i < possibleParents.size(); i++)
    {
        possibleParents.at(i)->id = i;
    }
}

bool BreedingTreeCalculator::doesCombinationContainAllSets(const std::vector<unsigned int> &combination) const
{
    long long target = 0b1 << conditions.size();
    target--;

    long long score = 0b0;

    for (const auto& index : combination)
    {
        score = score | possibleParentSets.at(index);
    }

    return target == score;
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

std::vector<std::shared_ptr<Dragon>> BreedingTreeCalculator::getSeededCombinationPermutation(std::vector<unsigned int> combination, int seed) const
{
    std::vector<std::shared_ptr<Dragon>> permutation = decltype(permutation)();

    while(combination.size() > 0)
    {
        int index = seed % combination.size();
        seed = seed / combination.size();

        permutation.push_back(possibleParents.at(combination.at(index)));
        combination.erase(combination.cbegin() + index);
    }

    return permutation;
}

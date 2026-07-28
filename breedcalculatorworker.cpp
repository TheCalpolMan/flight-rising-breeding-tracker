#include "breedcalculatorworker.h"

#include <list>
#include <cassert>

#include "binarytreegenerator.h"

const std::multiset<BreedingTreeConfig> &BreedCalculatorWorker::getConfigs()
{
    if (!validTreeConfigs.empty())
    {
        return validTreeConfigs;
    }

    auto& treeGenerator = BinaryTreeGenerator::getInstance();

    int totalRuns = 0;

    for (int parentCount = 2; parentCount <= possibleParents.size(); parentCount++)
    {
        int permutationCount = nPr(possibleParents.size(), parentCount);
        totalRuns += permutationCount * treeGenerator.getCombinations(parentCount).size();
    }

    int percentageDoneStep = std::max(1, totalRuns / 99);
    int runsDone = 0;

    for (int parentCount = 2; parentCount <= possibleParents.size(); parentCount++)
    {
        int permutationCount = nPr(possibleParents.size(), parentCount);

        for (int permutationSeed = 0; permutationSeed < permutationCount; permutationSeed++)
        {
            auto permutation = getPossibleParentPermutationFromSeed(parentCount, permutationSeed);

            for (const auto& binaryTree : treeGenerator.getCombinations(parentCount))
            {
                BreedingTreeConfig config = BreedingTreeConfig(aim, permutation, std::make_shared<BinaryTreePossibilityNode>(binaryTree, permutation));

                runsDone++;

                if ((runsDone % percentageDoneStep) == 0)
                {
                    emit progressUpdate(runsDone / percentageDoneStep);
                }

                if (!doesConfigHaveValidPairings(config))
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

    emit progressUpdate(100);

    return validTreeConfigs;
}

int BreedCalculatorWorker::factorial(int n)
{
    int value = 1;

    for (int i = 2; i <= n; i++)
    {
        value *= i;
    }

    return value;
}

int BreedCalculatorWorker::nPr(int n, int r)
{
    return factorial(n) / factorial(n - r);
}

std::vector<std::shared_ptr<Dragon>> BreedCalculatorWorker::convertDragonsToSharedPtr(const std::vector<Dragon> &dragons)
{
    std::vector<std::shared_ptr<Dragon>> sharedDragons = decltype(sharedDragons)();

    for(const auto& dragon : dragons)
    {
        sharedDragons.push_back(std::make_shared<Dragon>(dragon));
    }

    return sharedDragons;
}

bool BreedCalculatorWorker::doesConfigHaveValidPairings(const BreedingTreeConfig &config)
{
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

std::vector<std::shared_ptr<Dragon>> BreedCalculatorWorker::getPossibleParentPermutationFromSeed(int count, int seed) const
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

void BreedCalculatorWorker::doWork(const std::multiset<BreedingTreeConfig> &parameter, std::vector<std::shared_ptr<Dragon> > possibleParents, std::shared_ptr<Dragon> aim)
{
    if (this->aim != aim || this->possibleParents != possibleParents)
    {
        validTreeConfigs.clear();

        this->aim = aim;
        this->possibleParents = possibleParents;
    }

    emit resultReady(getConfigs());
}

BreedCalculatorWorker::BreedCalculatorWorker(QObject *parent)
    : QObject{parent}
{}

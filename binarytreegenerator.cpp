#include "binarytreegenerator.h"

#include <stdexcept>

std::vector<std::shared_ptr<BinaryTreeNode>>& BinaryTreeGenerator::getCombinations(int leafNodeCount)
{
    if (leafNodeCount < 1)
    {
        throw std::invalid_argument("Leaf node count must be greater than or equal to 1");
    }

    auto it = combinations.find(leafNodeCount);

    if (it != combinations.cend())
    {
        return it->second;
    }

    // make sure all lower combos are generated
    getCombinations(leafNodeCount - 1);

    std::vector<std::shared_ptr<BinaryTreeNode>> combos = decltype(combos)();

    // now we get to do some absolutely classic number bonds
    for(int i = 1; i < (leafNodeCount / 2 + 1); i++)
    {
        auto smallCombos = getCombinations(i);
        auto largeCombos = getCombinations(leafNodeCount - i);

        for (const auto& smallCombo : smallCombos)
        {
            for (const auto& largeCombo : largeCombos)
            {
                auto currentCombo = std::make_shared<BinaryTreeNode>();

                currentCombo->leftChild = smallCombo;
                currentCombo->rightChild = largeCombo;

                combos.push_back(std::move(currentCombo));
            }
        }
    }

    combinations.emplace(leafNodeCount, std::move(combos));
    return combinations.find(leafNodeCount)->second;
}

BinaryTreeGenerator::BinaryTreeGenerator()
{
    std::vector<std::shared_ptr<BinaryTreeNode>> oneCombos = decltype(oneCombos)();

    oneCombos.emplace_back(std::make_shared<BinaryTreeNode>());

    combinations.emplace(1, std::move(oneCombos));
}

#ifndef BINARYTREEGENERATOR_H
#define BINARYTREEGENERATOR_H

#include <vector>
#include <unordered_map>

#include "binarytreenode.h"

class BinaryTreeGenerator
{
public:
    static BinaryTreeGenerator& getInstance()
    {
        static BinaryTreeGenerator instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    BinaryTreeGenerator(BinaryTreeGenerator const&) = delete;
    void operator=(BinaryTreeGenerator const&) = delete;

    std::vector<std::shared_ptr<BinaryTreeNode>>& getCombinations(int leafNodeCount);

private:
    BinaryTreeGenerator();

    std::unordered_map<int, std::vector<std::shared_ptr<BinaryTreeNode>>> combinations = decltype(combinations)();
};

#endif // BINARYTREEGENERATOR_H

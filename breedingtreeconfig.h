#ifndef BREEDINGTREECONFIG_H
#define BREEDINGTREECONFIG_H

#include <vector>
#include <memory>

#include "dragon.h"
#include "binarytreenode.h"

class BreedingTreeConfig
{
public:
    BreedingTreeConfig(const std::vector<std::shared_ptr<Dragon>>& dragons, std::shared_ptr<BinaryTreeNode> treeRoot);

    const std::vector<std::shared_ptr<Dragon>> dragons;
    std::shared_ptr<BinaryTreeNode> treeRoot;

    float chance;

    bool operator<(const BreedingTreeConfig& other) const
    {
        return this->chance < other.chance;
    }

private:
    void calculateChance();
};

#endif // BREEDINGTREECONFIG_H

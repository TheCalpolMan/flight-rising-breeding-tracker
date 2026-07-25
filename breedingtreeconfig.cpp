#include "breedingtreeconfig.h"

#include "dragonpossibility.h"

BreedingTreeConfig::BreedingTreeConfig(const std::vector<std::shared_ptr<Dragon>>& dragons, std::shared_ptr<BinaryTreeNode> treeRoot) :
    dragons(dragons),
    treeRoot(treeRoot)
{

}

void BreedingTreeConfig::calculateChance()
{

}

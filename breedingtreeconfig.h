#ifndef BREEDINGTREECONFIG_H
#define BREEDINGTREECONFIG_H

#include <vector>
#include <memory>

#include "dragon.h"
#include "dragonindexes.h"
#include "binarytreepossibilitynode.h"

class BreedingTreeConfig
{
public:
    BreedingTreeConfig(std::shared_ptr<Dragon> aim, const std::vector<std::shared_ptr<Dragon>>& dragons, std::shared_ptr<BinaryTreePossibilityNode> treeRoot);

    double getChance();

    double getCalculatedChance() const;

    const std::vector<std::shared_ptr<Dragon>>& getDragons() const;

    std::shared_ptr<BinaryTreePossibilityNode> treeRoot;

    bool operator<(const BreedingTreeConfig& other) const
    {
        return this->chance < other.chance;
    }

private:
    double getIndividualChance(const std::unordered_map<int, double>& target, int key);

    double chance = -1;
    DragonIndexes dragonIndexes;
    std::shared_ptr<Dragon> aim;
    std::vector<std::shared_ptr<Dragon>> dragons;
};

#endif // BREEDINGTREECONFIG_H

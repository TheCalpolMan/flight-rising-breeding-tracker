#ifndef BREEDINGTREECONFIG_H
#define BREEDINGTREECONFIG_H

#include <vector>
#include <memory>

#include "dragon.h"
#include "binarytreepossibilitynode.h"

class BreedingTreeConfig
{
public:
    BreedingTreeConfig(std::shared_ptr<Dragon> aim, const std::vector<std::shared_ptr<Dragon>>& dragons, std::shared_ptr<BinaryTreePossibilityNode> treeRoot);

    double getChance();

    double getCalculatedChance() const;

    const std::vector<std::shared_ptr<Dragon>> dragons;
    std::shared_ptr<BinaryTreePossibilityNode> treeRoot;

    bool operator<(const BreedingTreeConfig& other) const
    {
        return this->chance < other.chance;
    }

private:
    double getIndividualChance(const std::unordered_map<int, double>& target, int key);

    std::shared_ptr<Dragon> aim;
    double chance = -1;
};

#endif // BREEDINGTREECONFIG_H

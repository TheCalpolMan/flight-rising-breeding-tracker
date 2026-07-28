#include "breedingtreeconfig.h"

#include "information.h"
#include "vectorhelpers.h"

BreedingTreeConfig::BreedingTreeConfig(std::shared_ptr<Dragon> aim, const std::vector<std::shared_ptr<Dragon>>& dragons, std::shared_ptr<BinaryTreePossibilityNode> treeRoot) :
    dragons(dragons),
    treeRoot(treeRoot),
    aim(aim),
    dragonIndexes(*aim)
{

}

double BreedingTreeConfig::getChance()
{
    if (chance != -1)
    {
        return chance;
    }

    const auto& information = Information::getInstance();
    treeRoot->propogate();

    chance = 1;

    // TODO potentially return on chance == 0 to save on complexity?

    chance *= getIndividualChance(treeRoot->possibility->breed, dragonIndexes.breed);
    chance *= getIndividualChance(treeRoot->possibility->primaryColour, dragonIndexes.primaryColour);
    chance *= getIndividualChance(treeRoot->possibility->secondaryColour, dragonIndexes.secondaryColour);
    chance *= getIndividualChance(treeRoot->possibility->primaryGene, dragonIndexes.primaryGene);
    chance *= getIndividualChance(treeRoot->possibility->secondaryGene, dragonIndexes.secondaryGene);
    chance *= getIndividualChance(treeRoot->possibility->tertiaryGene, dragonIndexes.tertiaryGene);

    if (aim->tertiaryGene.string == "Basic")
    {
        chance *= getIndividualChance(treeRoot->possibility->tertiaryColour, dragonIndexes.tertiaryColour);
    }

    return chance;
}

double BreedingTreeConfig::getCalculatedChance() const
{
    return chance;
}

double BreedingTreeConfig::getIndividualChance(const std::unordered_map<int, double> &target, int key)
{
    auto it = target.find(key);

    if (it == target.cend())
    {
        return 0;
    }

    return it->second;
}

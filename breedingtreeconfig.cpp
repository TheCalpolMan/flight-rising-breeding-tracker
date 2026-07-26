#include "breedingtreeconfig.h"

#include "information.h"
#include "vectorhelpers.h"

BreedingTreeConfig::BreedingTreeConfig(std::shared_ptr<Dragon> aim, const std::vector<std::shared_ptr<Dragon>>& dragons, std::shared_ptr<BinaryTreePossibilityNode> treeRoot) :
    dragons(dragons),
    treeRoot(treeRoot),
    aim(aim)
{

}

long double BreedingTreeConfig::getChance()
{
    if (chance != -1)
    {
        return chance;
    }

    const auto& information = Information::getInstance();
    treeRoot->propogate();

    chance = 1;

    // TODO potentially return on chance == 0 to save on complexity?

    chance *= getIndividualChance(treeRoot->possibility->breed, VectorHelpers::getIndex(information.getBreeds(), aim->breed));
    chance *= getIndividualChance(treeRoot->possibility->primaryColour, VectorHelpers::getIndex(information.getColours(true), aim->primaryColour));
    chance *= getIndividualChance(treeRoot->possibility->secondaryColour, VectorHelpers::getIndex(information.getColours(true), aim->secondaryColour));
    chance *= getIndividualChance(treeRoot->possibility->tertiaryColour, VectorHelpers::getIndex(information.getColours(true), aim->tertiaryColour));
    chance *= getIndividualChance(treeRoot->possibility->primaryGene, VectorHelpers::getIndex(information.getPrimaryGenes(), aim->primaryGene));
    chance *= getIndividualChance(treeRoot->possibility->secondaryGene, VectorHelpers::getIndex(information.getSecondaryGenes(), aim->secondaryGene));
    chance *= getIndividualChance(treeRoot->possibility->tertiaryGene, VectorHelpers::getIndex(information.getTertiaryGenes(), aim->tertiaryGene));

    return chance;
}

long double BreedingTreeConfig::getIndividualChance(const std::unordered_map<int, long double> &target, int key)
{
    auto it = target.find(key);

    if (it == treeRoot->possibility->breed.cend())
    {
        return 0;
    }

    return it->second;
}

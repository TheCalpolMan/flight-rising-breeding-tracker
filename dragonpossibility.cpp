#include "dragonpossibility.h"

#include "information.h"
#include "vectorhelpers.h"

DragonPossibility::DragonPossibility(const Dragon& base) :
    DragonPossibility()
{
    Information& information = Information::getInstance();

    breed.insert(std::make_pair(VectorHelpers::getIndex(information.getBreeds(), base.breed), 1));

    primaryColour.insert(std::make_pair(base.primaryColour.wheelIndex, 1));
    secondaryColour.insert(std::make_pair(base.secondaryColour.wheelIndex, 1));
    tertiaryColour.insert(std::make_pair(base.tertiaryColour.wheelIndex, 1));

    primaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getPrimaryGenes(), base.primaryGene), 1));
    secondaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getSecondaryGenes(), base.secondaryGene), 1));
    tertiaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getTertiaryGenes(), base.tertiaryGene), 1));
}

DragonPossibility::DragonPossibility(const Dragon& parent1, const Dragon& parent2) :
    DragonPossibility(DragonPossibility(parent1), DragonPossibility(parent2))
{}

DragonPossibility::DragonPossibility(const DragonPossibility& parent1, const DragonPossibility& parent2) :
    DragonPossibility()
{
    Information& information = Information::getInstance();

    addGeneChances(breed, information.getBreeds(), parent1.breed, parent2.breed);

    addGeneChances(primaryGene, information.getPrimaryGenes(), parent1.primaryGene, parent2.primaryGene);
    addGeneChances(secondaryGene, information.getSecondaryGenes(), parent1.secondaryGene, parent2.secondaryGene);
    addGeneChances(tertiaryGene, information.getTertiaryGenes(), parent1.tertiaryGene, parent2.tertiaryGene);
}

void DragonPossibility::addGeneChances(std::unordered_map<int, int>& targetGene,
                                       const std::vector<Allele>& possibleGenes,
                                       const std::unordered_map<int, int>& parent1,
                                       const std::unordered_map<int, int>& parent2)
{
    Information& information = Information::getInstance();

    for (const auto& breedWeightPair1 : parent1)
    {
        for (const auto& breedWeightPair2 : parent2)
        {
            auto chances = information.getRarityChances(possibleGenes.at(breedWeightPair1.first).rarity,
                                                        possibleGenes.at(breedWeightPair2.first).rarity);

            addChance(targetGene, breedWeightPair1.first, chances.first * breedWeightPair1.second * breedWeightPair2.second);
            addChance(targetGene, breedWeightPair2.first, chances.second * breedWeightPair1.second * breedWeightPair2.second);
        }
    }
}

static void addChance(std::unordered_map<int, int>& possibilities, int key, int value)
{
    auto it = possibilities.find(key);

    if (it != possibilities.cend())
    {
        value += it->second;
        possibilities.erase(it);
    }

    possibilities.insert(key, value);
}

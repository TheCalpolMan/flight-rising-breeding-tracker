#include "dragonpossibility.h"

#include <cassert>

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

void DragonPossibility::addGeneChances(std::unordered_map<int, long double>& targetGene,
                                       const std::vector<Allele>& possibleGenes,
                                       const std::unordered_map<int, long double>& parent1,
                                       const std::unordered_map<int, long double>& parent2)
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

void DragonPossibility::addColourChances(std::unordered_map<int, long double>& targetColour,
                                          const std::vector<Colour>& possibleColours,
                                          const std::unordered_map<int, long double>& parent1,
                                          const std::unordered_map<int, long double>& parent2)
{
    Information& information = Information::getInstance();

    for (const auto& breedWeightPair1 : parent1)
    {
        for (const auto& breedWeightPair2 : parent2)
        {
            long double chance = breedWeightPair1.second * breedWeightPair2.second;

            int distance = breedWeightPair2.first - breedWeightPair1.first;

            int startIndex = breedWeightPair1.first;
            int endIndex = breedWeightPair2.first;

            if (distance > (information.getColours(true).size() / 2))
            {
                distance = std::abs(breedWeightPair1.first - breedWeightPair2.first);

                int startIndex = breedWeightPair2.first;
                int endIndex = breedWeightPair1.first;
            }


        }
    }
}

void DragonPossibility::addChance(std::unordered_map<int, long double>& possibilities, int key, long double value)
{
    auto it = possibilities.find(key);

    if (it != possibilities.cend())
    {
        value += it->second;
        possibilities.erase(it);
    }

    possibilities.emplace(key, value);
}

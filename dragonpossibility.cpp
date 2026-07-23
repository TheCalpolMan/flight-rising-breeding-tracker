#include "dragonpossibility.h"

#include <cmath>
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

    setGeneWeights(breed, information.getBreeds(), parent1.breed, parent2.breed);

    setGeneWeights(primaryGene, information.getPrimaryGenes(), parent1.primaryGene, parent2.primaryGene);
    setGeneWeights(secondaryGene, information.getSecondaryGenes(), parent1.secondaryGene, parent2.secondaryGene);
    setGeneWeights(tertiaryGene, information.getTertiaryGenes(), parent1.tertiaryGene, parent2.tertiaryGene);

    setColourWeights(primaryColour, parent1.primaryColour, parent2.primaryColour);
    setColourWeights(secondaryColour, parent1.secondaryColour, parent2.secondaryColour);
    setColourWeights(tertiaryColour, parent1.tertiaryColour, parent2.tertiaryColour);

    // all weights propogated, now to raise them to ^ 1.5, as an average of 3 children are born
    // but genders don't match up 50% of the time (so there are averagely 1.5 usable kids per pairing)

    auto raiseToPower = [](long double value){
        return value * std::sqrt(value);
    };

    modifyAllWeights(breed, raiseToPower);

    modifyAllWeights(primaryGene, raiseToPower);
    modifyAllWeights(secondaryGene, raiseToPower);
    modifyAllWeights(tertiaryGene, raiseToPower);

    modifyAllWeights(primaryColour, raiseToPower);
    modifyAllWeights(secondaryColour, raiseToPower);
    modifyAllWeights(tertiaryColour, raiseToPower);
}

void DragonPossibility::setGeneWeights(std::unordered_map<int, long double>& targetGene,
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

            addWeight(targetGene, breedWeightPair1.first, chances.first * breedWeightPair1.second * breedWeightPair2.second);
            addWeight(targetGene, breedWeightPair2.first, chances.second * breedWeightPair1.second * breedWeightPair2.second);
        }
    }
}

void DragonPossibility::setColourWeights(std::unordered_map<int, long double>& targetColour,
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
                startIndex = breedWeightPair2.first;
                endIndex = breedWeightPair1.first;
            }

            for (int i = startIndex; i != endIndex; i = (i + 1) % information.getColours(false).size())
            {
                addWeight(targetColour, i, chance);
            }
        }
    }
}

void DragonPossibility::modifyAllWeights(std::unordered_map<int, long double>& targetWeights, std::function<long double(long double)> modification)
{
    std::unordered_map<int, long double> newWeights = decltype(newWeights)();

    for (const auto& kvPair : targetWeights)
    {
        newWeights.emplace(kvPair.first, modification(kvPair.second));
    }

    targetWeights = newWeights;
}

void DragonPossibility::addWeight(std::unordered_map<int, long double>& possibilities, int key, long double value)
{
    auto it = possibilities.find(key);

    if (it != possibilities.cend())
    {
        value += it->second;
        possibilities.erase(it);
    }

    possibilities.emplace(key, value);
}

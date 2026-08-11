#include "dragonpossibility.h"

#include <cmath>
#include <cassert>

#include "tracy/Tracy.hpp"

#include "modutils.h"
#include "vectorhelpers.h"

DragonPossibility::~DragonPossibility()
{
    std::free(primaryColour);
    std::free(secondaryColour);
    std::free(tertiaryColour);
}

DragonPossibility::DragonPossibility()
{
    setupColourMembers();
}

DragonPossibility::DragonPossibility(const Dragon& base) :
    name(base.name),
    gender(base.male ? Gender::Male : Gender::Female)
{
    Information& information = Information::getInstance();
    setupColourMembers();

    breed.insert(std::make_pair(VectorHelpers::getIndex(information.getBreeds(), base.breed), 1));

    primaryColour[base.primaryColour.wheelIndex] = 1;
    secondaryColour[base.secondaryColour.wheelIndex] = 1;
    tertiaryColour[base.tertiaryColour.wheelIndex] = 1;

    primaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getPrimaryGenes(), base.primaryGene), 1));
    secondaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getSecondaryGenes(), base.secondaryGene), 1));
    tertiaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getTertiaryGenes(), base.tertiaryGene), 1));
}

DragonPossibility::DragonPossibility(const DragonPossibility& parent1, const DragonPossibility& parent2)
{
    ZoneScoped;
    Information& information = Information::getInstance();
    setupColourMembers();

    setGeneWeights(breed, information.getBreeds(), parent1.breed, parent2.breed);

    setGeneWeights(primaryGene, information.getPrimaryGenes(), parent1.primaryGene, parent2.primaryGene);
    setGeneWeights(secondaryGene, information.getSecondaryGenes(), parent1.secondaryGene, parent2.secondaryGene);
    setGeneWeights(tertiaryGene, information.getTertiaryGenes(), parent1.tertiaryGene, parent2.tertiaryGene);

    setColourWeights(primaryColour, parent1.primaryColour, parent2.primaryColour);
    setColourWeights(secondaryColour, parent1.secondaryColour, parent2.secondaryColour);
    setColourWeights(tertiaryColour, parent1.tertiaryColour, parent2.tertiaryColour);
}

void DragonPossibility::setupColourMembers()
{
    ZoneScoped;
    colourCount = Information::getInstance().getColours(true).size();

    primaryColour = reinterpret_cast<double*>(std::calloc(colourCount, sizeof(double)));
    secondaryColour = reinterpret_cast<double*>(std::calloc(colourCount, sizeof(double)));
    tertiaryColour = reinterpret_cast<double*>(std::calloc(colourCount, sizeof(double)));
}

void DragonPossibility::setGeneWeights(std::unordered_map<int, double>& targetGene,
                                       const std::vector<Allele>& possibleGenes,
                                       const std::unordered_map<int, double>& parent1,
                                       const std::unordered_map<int, double>& parent2)
{
    ZoneScoped;
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

void DragonPossibility::setColourWeights(double *targetColour, const double *parent1, const double *parent2)
{
    ZoneScoped;

    std::vector<int> parent2Indexes = decltype(parent2Indexes)();

    for (int parent2Index = 0; parent2Index < colourCount; parent2Index++)
    {
        if (parent2[parent2Index] == 0)
        {
            continue;
        }

        parent2Indexes.push_back(parent2Index);
    }

    for (int parent1Index = 0; parent1Index < colourCount; parent1Index++)
    {
        if (parent1[parent1Index] == 0)
        {
            continue;
        }

        for (int parent2Index : parent2Indexes)
        {
            int startIndex = parent1Index;
            int endIndex = (parent2Index + 1) % colourCount;

            int distance = ModUtils::getDisplacement(startIndex, endIndex, colourCount);

            if (distance <= 0)
            {
                startIndex = parent2Index;
                endIndex = (parent1Index + 1)  % colourCount;

                distance = ModUtils::getDisplacement(startIndex, endIndex, colourCount);
            }

            double chance = parent1[parent1Index] * parent2[parent2Index] / distance;

            for (int i = startIndex; i != endIndex; i = (i + 1) % colourCount)
            {
                targetColour[i] += chance;
            }
        }
    }
}

void DragonPossibility::modifyAllWeights(std::unordered_map<int, double>& targetWeights, std::function<double(double)> modification)
{
    std::unordered_map<int, double> newWeights = decltype(newWeights)();

    for (const auto& kvPair : targetWeights)
    {
        newWeights.emplace(kvPair.first, modification(kvPair.second));
    }

    targetWeights = newWeights;
}

void DragonPossibility::addWeight(std::unordered_map<int, double>& possibilities, int key, double value)
{
    auto it = possibilities.find(key);

    if (it != possibilities.cend())
    {
        value += it->second;
        possibilities.erase(it);
    }

    possibilities.emplace(key, value);
}

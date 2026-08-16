#include "dragonpossibility.h"

#include <list>
#include <cmath>

#include "tracy/Tracy.hpp"

#include "modutils.h"
#include "information.h"
#include "vectorhelpers.h"

DragonPossibility::~DragonPossibility()
{
    std::free(primaryColour);
    std::free(secondaryColour);
    std::free(tertiaryColour);
}

unsigned long long DragonPossibility::getCombinedLineage(int generations) const
{
    unsigned long long combined = 0b0;

    for (int i = 0; i < generations; i++)
    {
        combined = combined | lineage[i];
    }

    return combined;
}

DragonPossibility::DragonPossibility()
{
    setupColourMembers();
}

DragonPossibility::DragonPossibility(std::shared_ptr<Dragon> base) :
    name(base->name),
    gender(base->male ? Gender::Male : Gender::Female)
{
    Information& information = Information::getInstance();
    setupColourMembers();

    breed.insert(std::make_pair(VectorHelpers::getIndex(information.getBreeds(), base->breed), 1));

    primaryColour[base->primaryColour.wheelIndex] = 1;
    secondaryColour[base->secondaryColour.wheelIndex] = 1;
    tertiaryColour[base->tertiaryColour.wheelIndex] = 1;

    primaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getPrimaryGenes(), base->primaryGene), 1));
    secondaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getSecondaryGenes(), base->secondaryGene), 1));
    tertiaryGene.insert(std::make_pair(VectorHelpers::getIndex(information.getTertiaryGenes(), base->tertiaryGene), 1));

    setLineage(base);
    calculateInbred();
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

    for (int i = 1; i < 5; i++)
    {
        lineage[i] = parent1.lineage[i - 1] | parent2.lineage[i - 1];
    }

    calculateInbred(parent1, parent2);
}

void DragonPossibility::setLineage(std::shared_ptr<Dragon> base)
{
    if (base->id < 0)
    {
        throw std::invalid_argument("Base dragon has an unititialised ID");
    }

    if (base->id > 64)
    {
        throw std::runtime_error("Run out of unique dragon IDs, please restart session!");
    }

    lineage[0] = 1 << base->id;

    std::list<std::pair<int, std::shared_ptr<Dragon>>> relations = decltype(relations)();
    relations.emplace_back(-1, base);

    while(!relations.empty())
    {
        auto currentRelation = relations.front();
        relations.pop_front();

        int generation = currentRelation.first + 1;

        lineage[generation] = lineage[generation] | (1 << currentRelation.second->id);

        for (const auto& secondOrderRelation : currentRelation.second->lineage)
        {
            if (secondOrderRelation.second.expired())
            {
                continue;
            }

            int secondOrderGeneration = generation + secondOrderRelation.first;

            if (secondOrderGeneration > 5)
            {
                continue;
            }

            relations.emplace_back(secondOrderGeneration, secondOrderRelation.second);
        }
    }
}

void DragonPossibility::calculateInbred()
{
    unsigned long long combinedOr = 0b0;
    unsigned long long combinedAdd = 0b0;

    for (int i = 0; i < 5; i++)
    {
        combinedOr = combinedOr | lineage[i];
        combinedAdd = combinedAdd + lineage[i];
    }

    inbred = inbred || (combinedOr != combinedAdd);
}

void DragonPossibility::calculateInbred(const DragonPossibility &parent1, const DragonPossibility &parent2)
{
    inbred = parent1.inbred || parent2.inbred;

    if (!inbred)
    {
        inbred = (parent1.getCombinedLineage() & parent2.getCombinedLineage()) != 0;
    }

    // potentially redundant because of the other two checks
    if (!inbred)
    {
        calculateInbred();
    }
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

#ifndef DRAGONPOSSIBILITY_H
#define DRAGONPOSSIBILITY_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "dragon.h"

class DragonPossibility
{
public:
    DragonPossibility() = default;

    DragonPossibility(const Dragon& base);

    DragonPossibility(const Dragon& parent1, const Dragon& parent2);

    DragonPossibility(const DragonPossibility& parent1, const DragonPossibility& parent2);

    std::unordered_map<int, long double> breed;

    std::unordered_map<int, long double> primaryColour;
    std::unordered_map<int, long double> secondaryColour;
    std::unordered_map<int, long double> tertiaryColour;

    std::unordered_map<int, long double> primaryGene;
    std::unordered_map<int, long double> secondaryGene;
    std::unordered_map<int, long double> tertiaryGene;
private:
    void setGeneWeights(std::unordered_map<int, long double>& targetGene,
                        const std::vector<Allele>& possibleGenes,
                        const std::unordered_map<int, long double>& parent1,
                        const std::unordered_map<int, long double>& parent2);

    void setColourWeights(std::unordered_map<int, long double>& targetColour,
                        const std::unordered_map<int, long double>& parent1,
                        const std::unordered_map<int, long double>& parent2);

    static void modifyAllWeights(std::unordered_map<int, long double>& targetWeights, std::function<long double(long double)> modification);

    static void addWeight(std::unordered_map<int, long double>& possibilities, int key, long double value);
};

#endif // DRAGONPOSSIBILITY_H

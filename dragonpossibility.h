#ifndef DRAGONPOSSIBILITY_H
#define DRAGONPOSSIBILITY_H

#include <vector>
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
    void addGeneChances(std::unordered_map<int, long double>& targetGene,
                        const std::vector<Allele>& possibleGenes,
                        const std::unordered_map<int, long double>& parent1,
                        const std::unordered_map<int, long double>& parent2);

    void addColourChances(std::unordered_map<int, long double>& targetColour,
                        const std::vector<Colour>& possibleColours,
                        const std::unordered_map<int, long double>& parent1,
                        const std::unordered_map<int, long double>& parent2);

    static void addChance(std::unordered_map<int, long double>& possibilities, int key, long double value);
};

#endif // DRAGONPOSSIBILITY_H

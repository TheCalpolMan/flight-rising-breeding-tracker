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

    std::unordered_map<int, int> breed;

    std::unordered_map<int, int> primaryColour;
    std::unordered_map<int, int> secondaryColour;
    std::unordered_map<int, int> tertiaryColour;

    std::unordered_map<int, int> primaryGene;
    std::unordered_map<int, int> secondaryGene;
    std::unordered_map<int, int> tertiaryGene;
private:
    void addGeneChances(std::unordered_map<int, int>& targetGene,
                        const std::vector<Allele>& possibleGenes,
                        const std::unordered_map<int, int>& parent1,
                        const std::unordered_map<int, int>& parent2);

    static void addChance(std::unordered_map<int, int>& possibilities, int key, int value);
};

#endif // DRAGONPOSSIBILITY_H

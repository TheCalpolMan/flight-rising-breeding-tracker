#ifndef DRAGONPOSSIBILITY_H
#define DRAGONPOSSIBILITY_H

#include <vector>
#include <functional>
#include <unordered_map>

#include "dragon.h"

class DragonPossibility
{
public:
    friend class DragonPossibilityFactory;

    std::unordered_map<int, long double> breed = decltype(breed)();

    std::unordered_map<int, long double> primaryColour = decltype(primaryColour)();
    std::unordered_map<int, long double> secondaryColour = decltype(secondaryColour)();
    std::unordered_map<int, long double> tertiaryColour = decltype(tertiaryColour)();

    std::unordered_map<int, long double> primaryGene = decltype(primaryGene)();
    std::unordered_map<int, long double> secondaryGene = decltype(secondaryGene)();
    std::unordered_map<int, long double> tertiaryGene = decltype(tertiaryGene)();
private:
    DragonPossibility() = default;

    DragonPossibility(const Dragon& base);

    DragonPossibility(const DragonPossibility& parent1, const DragonPossibility& parent2);

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

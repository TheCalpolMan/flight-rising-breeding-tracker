#ifndef DRAGONPOSSIBILITY_H
#define DRAGONPOSSIBILITY_H

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "dragon.h"
#include "gender.h"

class DragonPossibility
{
public:
    friend class DragonPossibilityFactory;

    const std::string name = "";
    const Gender gender = Gender::Any;

    std::unordered_map<int, double> breed = decltype(breed)();

    std::unordered_map<int, double> primaryColour = decltype(primaryColour)();
    std::unordered_map<int, double> secondaryColour = decltype(secondaryColour)();
    std::unordered_map<int, double> tertiaryColour = decltype(tertiaryColour)();

    std::unordered_map<int, double> primaryGene = decltype(primaryGene)();
    std::unordered_map<int, double> secondaryGene = decltype(secondaryGene)();
    std::unordered_map<int, double> tertiaryGene = decltype(tertiaryGene)();
private:
    DragonPossibility() = default;

    DragonPossibility(const Dragon& base);

    DragonPossibility(const DragonPossibility& parent1, const DragonPossibility& parent2);

    void setGeneWeights(std::unordered_map<int, double>& targetGene,
                        const std::vector<Allele>& possibleGenes,
                        const std::unordered_map<int, double>& parent1,
                        const std::unordered_map<int, double>& parent2);

    void setColourWeights(std::unordered_map<int, double>& targetColour,
                        const std::unordered_map<int, double>& parent1,
                        const std::unordered_map<int, double>& parent2);

    static void modifyAllWeights(std::unordered_map<int, double>& targetWeights, std::function<double(double)> modification);

    static void addWeight(std::unordered_map<int, double>& possibilities, int key, double value);
};

#endif // DRAGONPOSSIBILITY_H

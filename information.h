#ifndef INFORMATION_H
#define INFORMATION_H

#include <vector>
#include <utility>

#include "rarity.h"
#include "allele.h"
#include "colour.h"
#include "eyeallele.h"

class Information
{
public:
    static Information& getInstance()
    {
        static Information instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    Information(Information const&) = delete;
    void operator=(Information const&) = delete;

    const std::vector<EyeAllele>& getEyes() const;

    const std::vector<Allele>& getBreeds() const;

    const std::vector<Allele>& getPrimaryGenes() const;

    const std::vector<Allele>& getSecondaryGenes() const;

    const std::vector<Allele>& getTertiaryGenes() const;

    const std::vector<Colour>& getColours(bool sortByWheel) const;

    std::pair<int, int> getRarityChances(Rarity a, Rarity b);

    static int rarityToRank(Rarity rarity);
private:
    Information();

    std::vector<EyeAllele> eyes = decltype(eyes)();
    std::vector<Allele> breeds = decltype(breeds)();
    std::vector<Allele> primaryGenes = decltype(primaryGenes)();
    std::vector<Allele> secondaryGenes = decltype(secondaryGenes)();
    std::vector<Allele> tertiaryGenes = decltype(tertiaryGenes)();

    std::vector<Colour> colours = decltype(colours)();
    std::vector<Colour> coloursByWheel = decltype(coloursByWheel)();

    std::vector<std::vector<std::pair<int, int>>> rarityChances = decltype(rarityChances)();
};

#endif // INFORMATION_H

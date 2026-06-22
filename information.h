#ifndef INFORMATION_H
#define INFORMATION_H

#include <vector>

#include "allele.h"
#include "colour.h"

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

    std::vector<Allele> getBreeds() const;

    std::vector<Allele> getPrimaryGenes() const;

    std::vector<Allele> getSecondaryGenes() const;

    std::vector<Allele> getTertiaryGenes() const;

    std::vector<Colour> getColours() const;
private:
    Information();

    std::vector<Allele> breeds = decltype(breeds)();
    std::vector<Allele> primaryGenes = decltype(primaryGenes)();
    std::vector<Allele> secondaryGenes = decltype(secondaryGenes)();
    std::vector<Allele> tertiaryGenes = decltype(tertiaryGenes)();
    std::vector<Colour> colours = decltype(colours)();
};

#endif // INFORMATION_H

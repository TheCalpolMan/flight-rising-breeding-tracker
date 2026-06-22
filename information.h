#ifndef INFORMATION_H
#define INFORMATION_H

#include <unordered_map>
#include <unordered_set>

#include "raritystring.h"

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

    std::unordered_set<RarityString> getBreeds() const;

    std::unordered_set<RarityString> getPrimaryGenes() const;

    std::unordered_set<RarityString> getSecondaryGenes() const;

    std::unordered_set<RarityString> getTertiaryGenes() const;

    std::unordered_map<std::string, std::string> getColours() const;
private:
    Information();

    std::unordered_set<RarityString, RarityString::HashFunction> breeds = decltype(breeds)();
    std::unordered_set<RarityString, RarityString::HashFunction> primaryGenes = decltype(primaryGenes)();
    std::unordered_set<RarityString, RarityString::HashFunction> secondaryGenes = decltype(secondaryGenes)();
    std::unordered_set<RarityString, RarityString::HashFunction> tertiaryGenes = decltype(tertiaryGenes)();
    std::unordered_map<std::string, std::string> colours = decltype(colours)();
};

#endif // INFORMATION_H

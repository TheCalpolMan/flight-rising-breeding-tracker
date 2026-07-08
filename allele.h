#ifndef ALLELE_H
#define ALLELE_H

#include <string>

#include "rarity.h"

struct Allele
{
public:
    Rarity rarity;
    std::string string;
    bool ancient;
    std::string species;

    Allele() = default;

    Allele(Rarity rarity,std::string string, std::string ancientSpecies = "");

    bool operator==(const Allele& other) const
    {
        if (this->string == other.string)
        {
            return true;
        }

        return false;
    }

    struct HashFunction
    {
        size_t operator()(const Allele& rarityString) const
        {
            return std::hash<std::string>()(rarityString.string);
        }
    };
};

#endif // ALLELE_H

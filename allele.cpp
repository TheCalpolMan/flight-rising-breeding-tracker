#include "allele.h"

Allele::Allele(Rarity rarity, std::string string, std::string ancientSpecies)
{
    this->rarity = rarity;
    this->string = string;

    if (ancientSpecies == "")
    {
        ancient = false;
        this->species = "modern";
    }
    else
    {
        ancient = true;
        this->species = ancientSpecies;
    }

    this->ancient = ancient;
}

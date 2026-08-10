#include "allele.h"

Allele::Allele(std::string string, Rarity rarity, std::string ancientSpecies)
{
    this->string = string;
    this->rarity = rarity;

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

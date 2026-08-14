#include "dragon.h"

Dragon::Dragon(const std::string& name, bool male, const EyeAllele& eye, const Allele& breed,
    const Colour& primaryColour, const Colour& secondaryColour, const Colour& tertiaryColour,
    const Allele& primaryGene, const Allele& secondaryGene, const Allele& tertiaryGene) :
    name(name),
    male(male),
    eye(eye),
    breed(breed),
    primaryColour(primaryColour),
    secondaryColour(secondaryColour),
    tertiaryColour(tertiaryColour),
    primaryGene(primaryGene),
    secondaryGene(secondaryGene),
    tertiaryGene(tertiaryGene)
{

}

void Dragon::addLineage(int generation, std::shared_ptr<Dragon> progenitor)
{
    lineage.emplace_back(generation, std::weak_ptr<Dragon>(progenitor));
}

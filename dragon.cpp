#include "dragon.h"

Dragon::Dragon(const EyeAllele& eye, const Allele& breed,
    const Colour& primaryColour, const Colour& secondaryColour, const Colour& tertiaryColour,
    const Allele& primaryGene, const Allele& secondaryGene, const Allele& tertiaryGene) :
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

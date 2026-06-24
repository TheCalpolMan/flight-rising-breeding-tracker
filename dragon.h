#ifndef DRAGON_H
#define DRAGON_H

#include "colour.h"
#include "allele.h"
#include "eyeallele.h"

struct Dragon
{
public:
    int family = -1;

    Allele breed;
    EyeAllele eye;

    Colour primaryColour;
    Colour secondaryColour;
    Colour tertiaryColour;

    Allele primaryGene;
    Allele secondaryGene;
    Allele tertiaryGene;

    Dragon(const EyeAllele& eye, const Allele& breed,
       const Colour& primaryColour, const Colour& secondaryColour, const Colour& tertiaryColour,
       const Allele& primaryGene, const Allele& secondaryGene, const Allele& tertiaryGene);
};

#endif // DRAGON_H

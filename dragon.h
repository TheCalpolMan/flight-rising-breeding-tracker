#ifndef DRAGON_H
#define DRAGON_H

#include "colour.h"
#include "allele.h"

struct Dragon
{
public:
    int family = -1;

    Allele eye;
    Allele breed;

    Colour primaryColour;
    Colour secondaryColour;
    Colour tertiaryColour;

    Allele primaryGene;
    Allele secondaryGene;
    Allele tertiaryGene;

    Dragon(Allele eye, Allele breed,
       Colour primaryColour, Colour secondaryColour, Colour tertiaryColour,
       Allele primaryGene, Allele secondaryGene, Allele tertiaryGene);
};

#endif // DRAGON_H

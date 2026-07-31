#ifndef DRAGON_H
#define DRAGON_H

#include "colour.h"
#include "allele.h"
#include "eyeallele.h"

struct Dragon
{
public:
    unsigned long long family = 0b0;

    bool male = false;
    Allele breed;
    EyeAllele eye;

    Colour primaryColour;
    Colour secondaryColour;
    Colour tertiaryColour;

    Allele primaryGene;
    Allele secondaryGene;
    Allele tertiaryGene;

    std::string name = "";
    std::string imageLocation = "";

    Dragon() = default;

    Dragon(const std::string& name, bool male, const EyeAllele& eye, const Allele& breed,
       const Colour& primaryColour, const Colour& secondaryColour, const Colour& tertiaryColour,
       const Allele& primaryGene, const Allele& secondaryGene, const Allele& tertiaryGene);
};

#endif // DRAGON_H

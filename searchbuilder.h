#ifndef SEARCHBUILDER_H
#define SEARCHBUILDER_H

#include "dragon.h"

#include <vector>

class SearchBuilder
{
public:
    static std::string fromDragon(const Dragon& dragon, std::vector<int> colourRanges,
        std::vector<int> colourOffsets, bool primaryGene, bool secondaryGene, bool tertiaryGene, bool breed);

private:
    static const std::string delimiter;

    static int getIndex(const std::vector<Colour>& target, const Colour& value);

    static int getIndex(const std::vector<Allele>& target, const Allele& value);

    static void addColourRange(const Colour& colour, int range, int offset, std::stringstream& stream);

    static void addEqualOrRarerAlleles(const Allele& allele, const std::vector<Allele>& allAllelesOfType, std::stringstream& stream, int indexShift = 1);
};

#endif // SEARCHBUILDER_H

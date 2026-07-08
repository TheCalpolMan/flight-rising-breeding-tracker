#ifndef SEARCHBUILDER_H
#define SEARCHBUILDER_H

#include "dragon.h"
#include "gender.h"
#include "currency.h"
#include "saveformat.h"

#include <vector>

class SearchBuilder
{
public:
    static std::string fromSaveFormat(const SaveFormat& save, Gender gender, Currency currency);

    static std::string fromDragon(const Dragon& dragon, std::vector<int> colourRanges,
        std::vector<int> colourOffsets, bool primaryGene, bool secondaryGene, bool tertiaryGene, bool breed,
        Gender gender, Currency currency);

private:
    static const std::string delimiter;

    static void addColourRange(const Colour& colour, int range, int offset, std::stringstream& stream);

    static void addEqualOrRarerAlleles(const Allele& allele, const std::vector<Allele>& allAllelesOfType, std::stringstream& stream, int indexShift = 1);
};

#endif // SEARCHBUILDER_H

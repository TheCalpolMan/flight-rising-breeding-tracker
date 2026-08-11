#ifndef DRAGONREGEX_H
#define DRAGONREGEX_H

#include "dragon.h"

#include <boost/xpressive/xpressive.hpp>

class DragonRegex
{
public:
    static bool ConstructDragon(const std::string& paste, Dragon& dragon);
private:
    static boost::xpressive::sregex nameRegex;
    static boost::xpressive::sregex breedGenderRegex;

    static boost::xpressive::sregex primaryRegex;
    static boost::xpressive::sregex secondaryRegex;
    static boost::xpressive::sregex tertiaryRegex;

    static std::string getConcatenatedDragonBreeds();

    static Colour getColour(const std::vector<Colour>& possibleColours, const std::string &colourName);
    static Allele getAllele(const std::vector<Allele>& possibleAlleles, const std::string &alleleString);
};

#endif // DRAGONREGEX_H

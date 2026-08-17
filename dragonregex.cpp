#include "dragonregex.h"

#include <sstream>
#include <iostream>

#include "information.h"
#include "vectorhelpers.h"

bool DragonRegex::ConstructDragon(const std::string &paste, Dragon &dragon)
{
    auto& information = Information::getInstance();
    dragon.eye = information.getEyes().front();

    boost::xpressive::smatch match;

    if(!regex_search(paste, match, nameRegex))
    {
        return false;
    }

    dragon.name = match[1];

    if(!regex_search(paste, match, breedGenderRegex))
    {
        return false;
    }

    dragon.male = match[1] == "Male";

    Allele breed = getAllele(information.getBreeds(), match[4]);

    if (breed == Allele())
    {
        return false;
    }

    dragon.breed = breed;

    if(!regex_search(paste, match, primaryRegex))
    {
        return false;
    }

    Colour colour = getColour(information.getColours(true), match[1]);
    Allele gene = getAllele(information.getPrimaryGenes(), match[2]);

    if (colour == Colour() || gene == Allele())
    {
        return false;
    }

    dragon.primaryColour = colour;
    dragon.primaryGene = gene;

    if(!regex_search(paste, match, secondaryRegex))
    {
        return false;
    }

    colour = getColour(information.getColours(true), match[1]);
    gene = getAllele(information.getSecondaryGenes(), match[2]);

    if (colour == Colour() || gene == Allele())
    {
        return false;
    }

    dragon.secondaryColour = colour;
    dragon.secondaryGene = gene;

    if(!regex_search(paste, match, tertiaryRegex))
    {
        return false;
    }

    colour = getColour(information.getColours(true), match[1]);
    gene = getAllele(information.getTertiaryGenes(), match[2]);

    if (colour == Colour() || gene == Allele())
    {
        return false;
    }

    dragon.tertiaryColour = colour;
    dragon.tertiaryGene = gene;

    return true;
}

boost::xpressive::sregex DragonRegex::nameRegex = boost::xpressive::sregex::compile("\\S+ ?Lair ?» ?(\\S+)\n");
boost::xpressive::sregex DragonRegex::breedGenderRegex = boost::xpressive::sregex::compile("icon\\s*((Female)?(Male)?)\\s*(" + getConcatenatedDragonBreeds() + ")");

boost::xpressive::sregex DragonRegex::primaryRegex = boost::xpressive::sregex::compile("Primary Gene\\s+(\\S+)\\s+(.+)\\s+Secondary Gene");
boost::xpressive::sregex DragonRegex::secondaryRegex = boost::xpressive::sregex::compile("Secondary Gene\\s+(\\S+)\\s+(.+)\\s+Tertiary Gene");
boost::xpressive::sregex DragonRegex::tertiaryRegex = boost::xpressive::sregex::compile("Tertiary Gene\\s+(\\S+)\\s+(.+)\\s+Hatchday\\s*Hatchday");

std::string DragonRegex::getConcatenatedDragonBreeds()
{
    std::stringstream stream;

    for (const auto& breed : Information::getInstance().getBreeds())
    {
        stream << "(" << breed.string << ")";

        if (breed.string != Information::getInstance().getBreeds().back().string)
        {
            stream << "|";
        }
    }

    return stream.str();
}

Colour DragonRegex::getColour(const std::vector<Colour> &possibleColours, const std::string &colourName)
{
    for (const auto& colour : possibleColours)
    {
        if (colour.name == colourName)
        {
            return colour;
        }
    }

    return Colour();
}

Allele DragonRegex::getAllele(const std::vector<Allele> &possibleAlleles, const std::string& alleleString)
{
    for (const auto& allele : possibleAlleles)
    {
        if (allele.string == alleleString)
        {
            return allele;
        }
    }

    return Allele();
}

#include "searchbuilder.h"

#include <sstream>

#include "information.h"
#include "vectorhelpers.h"

const std::string SearchBuilder::delimiter = "%2C";

std::string SearchBuilder::fromSaveFormat(const SaveFormat& save, Gender gender, Currency currency)
{
    std::vector<int> colourRanges;
    std::vector<int> colourOffsets;

    colourRanges.push_back(save.primaryColourRange);
    colourRanges.push_back(save.secondaryColourRange);
    colourRanges.push_back(save.secondaryColourRange);

    colourOffsets.push_back(save.primaryColourOffset);
    colourOffsets.push_back(save.secondaryColourOffset);
    colourOffsets.push_back(save.secondaryColourOffset);

    return fromDragon(
        save.dragon,
        colourRanges,
        colourOffsets,
        save.primaryToggle,
        save.secondaryToggle,
        save.tertiaryToggle,
        save.breedToggle,
        gender,
        currency
    );
}

std::string SearchBuilder::fromDragon(const Dragon& dragon, std::vector<int> colourRanges,
    std::vector<int> colourOffsets, bool primaryGene, bool secondaryGene, bool tertiaryGene, bool breed,
    Gender gender, Currency currency)
{
    auto& information = Information::getInstance();

    std::stringstream search;
    search << "https://www1.flightrising.com/auction-house/buy/realm/dragons?";

    if (currency != Currency::Any)
    {
        search << "currency=";

        if (currency == Currency::Treasure)
        {
            search << "0&";
        }
        else
        {
            search << "1&";
        }
    }

    if (gender != Gender::Any)
    {
        search << "d_gender=";

        if (gender == Gender::Male)
        {
            search << "0&";
        }
        else
        {
            search << "1&";
        }
    }

    search << "d_breed=";

    if (!breed || dragon.breed.ancient)
    {
        search << VectorHelpers::getIndex(information.getBreeds(), dragon.breed) + 1;
    }
    else
    {
        addEqualOrRarerAlleles(dragon.breed, information.getBreeds(), search);
    }

    search << "&d_body_range=";
    addColourRange(dragon.primaryColour, colourRanges.at(0), colourOffsets.at(0), search);

    search << "&d_wings_range=";
    addColourRange(dragon.secondaryColour, colourRanges.at(1), colourOffsets.at(1), search);

    if (dragon.tertiaryGene.string != "Basic")
    {
        search << "&d_tert_range=";
        addColourRange(dragon.tertiaryColour, colourRanges.at(2), colourOffsets.at(2), search);
    }

    search << "&d_bodygene=";

    if (!primaryGene)
    {
        search << VectorHelpers::getIndex(information.getPrimaryGenes(), dragon.primaryGene);
    }
    else if (dragon.primaryGene.string != "Basic")
    {
        addEqualOrRarerAlleles(dragon.primaryGene, information.getPrimaryGenes(), search, 0);
    }

    search << "&d_winggene=";

    if (!secondaryGene)
    {
        search << VectorHelpers::getIndex(information.getSecondaryGenes(), dragon.secondaryGene);
    }
    else if (dragon.secondaryGene.string != "Basic")
    {
        addEqualOrRarerAlleles(dragon.secondaryGene, information.getSecondaryGenes(), search, 0);
    }

    if (dragon.tertiaryGene.string != "Basic")
    {
        search << "&d_tertgene=";

        if (!tertiaryGene)
        {
            search << VectorHelpers::getIndex(information.getTertiaryGenes(), dragon.tertiaryGene);
        }
        else
        {
            addEqualOrRarerAlleles(dragon.tertiaryGene, information.getTertiaryGenes(), search, 0);
        }
    }

    // std::string search = "https://www1.flightrising.com/auction-house/buy/realm/dragons?d_breed=502&d_body=502&d_eye=502&d_bodygene=502&d_winggene=502&d_tertgene=502&sort=expiration_desc&collapse=0";
    return search.str();
}

void SearchBuilder::addColourRange(const Colour& colour, int range, int offset, std::stringstream& stream)
{
    auto& information = Information::getInstance();

    Colour startColour = information.getColours(true).at((
        colour.wheelIndex - 1 - range + offset + information.getColours(true).size()) % information.getColours(true).size());

    Colour endColour = information.getColours(true).at((
        colour.wheelIndex - 1 + range + offset + information.getColours(true).size()) % information.getColours(true).size());

    stream << VectorHelpers::getIndex(information.getColours(false), startColour) + 1;
    stream << "-";
    stream << VectorHelpers::getIndex(information.getColours(false), endColour) + 1;
}

void SearchBuilder::addEqualOrRarerAlleles(const Allele& allele, const std::vector<Allele>& allAllelesOfType, std::stringstream& stream, int indexShift)
{
    auto& information = Information::getInstance();

    int rarityRank = information.rarityToRank(allele.rarity);

    bool firstDone = false;
    for (int i=0;i<allAllelesOfType.size();i++)
    {
        if (allele.ancient != allAllelesOfType.at(i).ancient && allele.species != allAllelesOfType.at(i).species)
        {
            continue;
        }

        if (information.rarityToRank(allAllelesOfType.at(i).rarity) < rarityRank)
        {
            continue;
        }

        if (firstDone)
        {
            stream << delimiter;
        }

        stream << i + indexShift;
        firstDone = true;
    }
}

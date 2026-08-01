#include "information.h"

#include <algorithm>

#include "csvreader.h"

Information::Information()
{
    // rarity chances

    auto unprocessedRarityChances = CsvReader("assets/rarity-chances.csv").getValues();

    for (int row = 0; row < unprocessedRarityChances.size(); row++)
    {
        std::vector<std::pair<float, float>> processedRow = decltype(processedRow)();

        for (int column = 0; column < unprocessedRarityChances.at(row).size(); column++)
        {
            const std::string& workingValue = unprocessedRarityChances.at(row).at(column);

            int slashPos = workingValue.find('/');

            processedRow.push_back(std::make_pair(
                std::stof(workingValue.substr(0, slashPos)),
                std::stof(workingValue.substr(slashPos + 1))));
        }

        rarityChances.push_back(std::move(processedRow));
    }

    // eyes
    {

    }

    // breeds
    {

    }

    // primary genes
    {

    }

    // secondary genes
    {

    }

    // tertiary genes
    {

    }

    // Colours
    {


        coloursByWheel = colours;
        std::sort(coloursByWheel.begin(), coloursByWheel.end(),
            [](const Colour& a, const Colour& b)
            {
                return a.wheelIndex < b.wheelIndex;
            }
        );
    }
}

const std::vector<EyeAllele>& Information::getEyes() const
{
    return eyes;
}

const std::vector<Allele>& Information::getBreeds() const
{
    return breeds;
}

const std::vector<Allele>& Information::getPrimaryGenes() const
{
    return primaryGenes;
}

const std::vector<Allele>& Information::getSecondaryGenes() const
{
    return secondaryGenes;
}

const std::vector<Allele>& Information::getTertiaryGenes() const
{
    return tertiaryGenes;
}

const std::vector<Colour>& Information::getColours(bool sortByWheel) const
{
    if (!sortByWheel)
    {
        return colours;
    }

    return coloursByWheel;
}

int Information::rarityToRank(Rarity rarity)
{
    switch (rarity)
    {
    case(Rarity::Spacer): return 0;
    case(Rarity::Plentiful): return 1;
    case(Rarity::Common): return 2;
    case(Rarity::Uncommon): return 3;
    case(Rarity::Limited): return 4;
    case(Rarity::Rare): return 5;
    default:return -1;
    }
}

std::pair<float, float> Information::getRarityChances(Rarity a, Rarity b)
{
    return rarityChances.at(rarityToRank(a) - 1).at(rarityToRank(b) - 1);
}

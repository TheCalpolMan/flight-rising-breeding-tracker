#include "information.h"

#include <algorithm>

#include "csvreader.h"

Information::Information()
{
    readEyes();
    readColours();
    readRarityChances();

    readAlleles(breeds, "assets/breeds.csv");
    readAlleles(primaryGenes, "assets/primary-genes.csv");
    readAlleles(secondaryGenes, "assets/secondary-genes.csv");
    readAlleles(tertiaryGenes, "assets/tertiary-genes.csv");
}

void Information::readAlleles(std::vector<Allele> &destinationVector, const std::string& filePath)
{
    auto unprocessedRows = CsvReader(filePath).getValues();

    for(const auto& row : unprocessedRows)
    {
        Rarity rarity = stringToRarity(row.at(1));

        if (rarity == Rarity::Spacer)
        {
            destinationVector.emplace_back("", Rarity::Spacer);
            continue;
        }

        if (row.at(2) == "Modern")
        {
            destinationVector.emplace_back(row.at(0), rarity);
            continue;
        }

        destinationVector.emplace_back(row.at(0), rarity, row.at(2));
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

Rarity Information::stringToRarity(const std::string &string)
{
    static std::unordered_map<std::string, Rarity> map = decltype(map)(
    {
        {"Plentiful", Rarity::Plentiful},
        {"Common", Rarity::Common},
        {"Uncommon", Rarity::Uncommon},
        {"Limited", Rarity::Limited},
        {"Rare", Rarity::Rare},
        {"Ancient", Rarity::Ancient},
        {"Spacer", Rarity::Spacer}
    });

    return map.find(string)->second;
}

std::pair<float, float> Information::getRarityChances(Rarity a, Rarity b)
{
    return rarityChances.at(rarityToRank(a) - 1).at(rarityToRank(b) - 1);
}

void Information::readEyes()
{
    auto unprocessedRows = CsvReader("assets/eyes.csv").getValues();

    for(const auto& row : unprocessedRows)
    {
        eyes.emplace_back(row.at(0), std::stoi(row.at(1)));
    }
}

void Information::readColours()
{
    auto unprocessedRows = CsvReader("assets/colours.csv").getValues();

    for (const auto& row : unprocessedRows)
    {
        colours.emplace_back(row.at(0), row.at(1), std::stoi(row.at(2)));
    }

    coloursByWheel = colours;
    std::sort(coloursByWheel.begin(), coloursByWheel.end(),
        [](const Colour& a, const Colour& b)
        {
            return a.wheelIndex < b.wheelIndex;
        }
    );
}

void Information::readRarityChances()
{
    auto unprocessedRows = CsvReader("assets/rarity-chances.csv").getValues();

    for (int row = 0; row < unprocessedRows.size(); row++)
    {
        std::vector<std::pair<float, float>> processedRow = decltype(processedRow)();

        for (int column = 0; column < unprocessedRows.at(row).size(); column++)
        {
            const std::string& workingValue = unprocessedRows.at(row).at(column);

            int slashPos = workingValue.find('/');

            processedRow.push_back(std::make_pair(
                std::stof(workingValue.substr(0, slashPos)),
                std::stof(workingValue.substr(slashPos + 1))));
        }

        rarityChances.push_back(std::move(processedRow));
    }
}

#include "information.h"

Information::Information()
{
    // breeds
    {
        breeds.insert(RarityString(Rarity::Plentiful, "Fae"));
        breeds.insert(RarityString(Rarity::Plentiful, "Guardian"));
        breeds.insert(RarityString(Rarity::Plentiful, "Mirror"));
        breeds.insert(RarityString(Rarity::Plentiful, "Tundra"));

        breeds.insert(RarityString(Rarity::Common, "Pearlcatcher"));
        breeds.insert(RarityString(Rarity::Common, "Ridgeback"));
        breeds.insert(RarityString(Rarity::Common, "Snapper"));
        breeds.insert(RarityString(Rarity::Common, "Spiral"));

        breeds.insert(RarityString(Rarity::Uncommon, "Bogsneak"));
        breeds.insert(RarityString(Rarity::Uncommon, "Fathom"));
        breeds.insert(RarityString(Rarity::Uncommon, "Skydancer"));
        breeds.insert(RarityString(Rarity::Uncommon, "Obelisk"));

        breeds.insert(RarityString(Rarity::Limited, "Imperial"));
        breeds.insert(RarityString(Rarity::Limited, "Nocturne"));

        breeds.insert(RarityString(Rarity::Rare, "Coatl"));
        breeds.insert(RarityString(Rarity::Rare, "Wildclaw"));

        breeds.insert(RarityString(Rarity::Ancient, "Aberration"));
        breeds.insert(RarityString(Rarity::Ancient, "Aether"));
        breeds.insert(RarityString(Rarity::Ancient, "Auraboa"));
        breeds.insert(RarityString(Rarity::Ancient, "Banescale"));
        breeds.insert(RarityString(Rarity::Ancient, "Cirrus"));
        breeds.insert(RarityString(Rarity::Ancient, "Dusthide"));
        breeds.insert(RarityString(Rarity::Ancient, "Everlux"));
        breeds.insert(RarityString(Rarity::Ancient, "Gaoler"));
        breeds.insert(RarityString(Rarity::Ancient, "Sandsurge"));
        breeds.insert(RarityString(Rarity::Ancient, "Thorntail"));
        breeds.insert(RarityString(Rarity::Ancient, "Undertide"));
        breeds.insert(RarityString(Rarity::Ancient, "Veilspun"));
        breeds.insert(RarityString(Rarity::Ancient, "Vigil"));
    }

    // genes
}

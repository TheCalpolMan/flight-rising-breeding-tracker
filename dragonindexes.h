#ifndef DRAGONINDEXES_H
#define DRAGONINDEXES_H

#include "dragon.h"

struct DragonIndexes
{
    DragonIndexes() = default;

    DragonIndexes(const Dragon& dragon);

    int breed;

    int primaryColour;
    int secondaryColour;
    int tertiaryColour;

    int primaryGene;
    int secondaryGene;
    int tertiaryGene;
};

#endif // DRAGONINDEXES_H

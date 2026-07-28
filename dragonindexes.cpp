#include "dragonindexes.h"

#include "information.h"
#include "vectorhelpers.h"

DragonIndexes::DragonIndexes(const Dragon &dragon)
{
    const auto& information = Information::getInstance();

    breed = VectorHelpers::getIndex(information.getBreeds(), dragon.breed);

    primaryColour = dragon.primaryColour.wheelIndex;
    secondaryColour = dragon.secondaryColour.wheelIndex;
    tertiaryColour = dragon.tertiaryColour.wheelIndex;

    primaryGene = VectorHelpers::getIndex(information.getPrimaryGenes(), dragon.primaryGene);
    secondaryGene = VectorHelpers::getIndex(information.getSecondaryGenes(), dragon.secondaryGene);
    tertiaryGene = VectorHelpers::getIndex(information.getTertiaryGenes(), dragon.tertiaryGene);
}

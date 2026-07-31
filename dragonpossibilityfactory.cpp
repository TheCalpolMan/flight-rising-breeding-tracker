#include "dragonpossibilityfactory.h"

#include "tracy/Tracy.hpp"

void DragonPossibilityFactory::clear()
{
    dragonToPossibilityMap = decltype(dragonToPossibilityMap)();
    parentsToPossibilityMap = decltype(parentsToPossibilityMap)();
}

std::shared_ptr<DragonPossibility> DragonPossibilityFactory::constructPossiblilty(std::shared_ptr<Dragon> base)
{
    ZoneScoped;
    auto it = dragonToPossibilityMap.find(base);

    if (it != dragonToPossibilityMap.cend())
    {
        return it->second;
    }

    return dragonToPossibilityMap.emplace(base, std::shared_ptr<DragonPossibility>(new DragonPossibility(*base))).first->second;
}

std::shared_ptr<DragonPossibility> DragonPossibilityFactory::constructPossiblilty(std::shared_ptr<DragonPossibility> parent1, std::shared_ptr<DragonPossibility> parent2)
{
    ZoneScoped;
    if (parent1 > parent2)
    {
        auto temp = parent1;
        parent1 = parent2;
        parent2 = temp;
    }

    auto parentPair = std::make_pair(parent1, parent2);
    auto it = parentsToPossibilityMap.find(parentPair);

    if (it != parentsToPossibilityMap.cend())
    {
        return it->second;
    }

    return parentsToPossibilityMap.emplace(parentPair, std::shared_ptr<DragonPossibility>(new DragonPossibility(*parent1, *parent2))).first->second;
}

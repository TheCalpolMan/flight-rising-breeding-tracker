#ifndef DRAGONPOSSIBILITYFACTORY_H
#define DRAGONPOSSIBILITYFACTORY_H

#include <memory>
#include <utility>
#include <unordered_map>

#include "dragonpossibility.h"

class DragonPossibilityFactory
{
public:
    static DragonPossibilityFactory& getInstance()
    {
        static DragonPossibilityFactory instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

    DragonPossibilityFactory(DragonPossibilityFactory const&) = delete;
    void operator=(DragonPossibilityFactory const&) = delete;

    void clear();

    std::shared_ptr<DragonPossibility> constructPossiblilty(std::shared_ptr<Dragon> base);

    std::shared_ptr<DragonPossibility> constructPossiblilty(std::shared_ptr<DragonPossibility> parent1, std::shared_ptr<DragonPossibility> parent2);
private:
    struct DragonPossibilityPairHasher
    {
        std::size_t operator () (const std::pair<std::shared_ptr<DragonPossibility>, std::shared_ptr<DragonPossibility>> possibility) const
        {
            std::hash<std::shared_ptr<DragonPossibility>> hasher;

            std::size_t seed = hasher(possibility.first);

            // Source - https://stackoverflow.com/a/2595226
            // Posted by Karl von Moor
            // Retrieved 2026-07-25, License - CC BY-SA 2.5

            seed ^= hasher(possibility.second) + 0x9e3779b9 + (seed<<6) + (seed>>2);

            return seed;
        }
    };

    DragonPossibilityFactory() = default;

    std::unordered_map<std::shared_ptr<Dragon>, std::shared_ptr<DragonPossibility>> dragonToPossibilityMap = decltype(dragonToPossibilityMap)();
    std::unordered_map<std::pair<std::shared_ptr<DragonPossibility>, std::shared_ptr<DragonPossibility>>, std::shared_ptr<DragonPossibility>, DragonPossibilityPairHasher> parentsToPossibilityMap =
        decltype(parentsToPossibilityMap)();
};


#endif // DRAGONPOSSIBILITYFACTORY_H

#ifndef SAVEFORMAT_H
#define SAVEFORMAT_H

#include <string>
#include <vector>

#include <document.h>

#include "dragon.h"

class SaveFormat
{
public:
    SaveFormat(const Dragon& dragon, bool primaryToggle, bool secondaryToggle, bool tertiaryToggle,
               bool breedToggle, int primaryColourRange, int primaryColourOffset, int secondaryColourRange,
               int secondaryColourOffset, int tertiaryColourRange, int tertiaryColourOffset,
               const std::vector<std::shared_ptr<Dragon>>& pairingDragons);

    SaveFormat(const std::string& fileLocation);

    void write(const std::string& fileLocation);

    static rapidjson::Value writeDragon(const Dragon& dragon, rapidjson::MemoryPoolAllocator<>& allocator);

    static Dragon readDragon(const rapidjson::GenericValue<rapidjson::UTF8<>>& dragonRoot);

    Dragon dragon;

    bool primaryToggle;
    bool secondaryToggle;
    bool tertiaryToggle;
    bool breedToggle;

    int primaryColourRange;
    int primaryColourOffset;
    int secondaryColourRange;
    int secondaryColourOffset;
    int tertiaryColourRange;
    int tertiaryColourOffset;

    std::vector<std::shared_ptr<Dragon>> pairingDragons;
};

#endif // SAVEFORMAT_H

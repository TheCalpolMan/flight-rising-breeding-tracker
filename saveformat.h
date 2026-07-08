#ifndef SAVEFORMAT_H
#define SAVEFORMAT_H

#include <string>

#include "dragon.h"

class SaveFormat
{
public:
    static const std::string ending;

    SaveFormat(const Dragon& dragon, bool primaryToggle, bool secondaryToggle, bool tertiaryToggle,
               bool breedToggle, int primaryColourRange, int primaryColourOffset, int secondaryColourRange,
               int secondaryColourOffset, int tertiaryColourRange, int tertiaryColourOffset);

    SaveFormat(const std::string& fileLocation);

    void write(const std::string& fileLocation);

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
};

#endif // SAVEFORMAT_H

#ifndef DRAGONREGEX_H
#define DRAGONREGEX_H

#include "dragon.h"

class DragonRegex
{
public:
    static Dragon ConstructDragon(const std::string& paste);
private:
    static std::string getConcatenatedDragonBreeds();
};

#endif // DRAGONREGEX_H

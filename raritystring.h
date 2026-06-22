#ifndef RARITYSTRING_H
#define RARITYSTRING_H

#include <string>

#include "rarity.h"

struct RarityString
{
public:
    Rarity rarity;
    std::string string;

    RarityString(Rarity rarity,std::string string);

    bool operator==(const RarityString& otherString) const
    {
        if (this->string == otherString.string)
        {
            return true;
        }

        return false;
    }

    struct HashFunction
    {
        size_t operator()(const RarityString& rarityString) const
        {
            return std::hash<std::string>()(rarityString.string);
        }
    };
};

#endif // RARITYSTRING_H

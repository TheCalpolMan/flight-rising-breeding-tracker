#ifndef COLOUR_H
#define COLOUR_H

#include <string>

struct Colour
{
public:
    int wheelIndex;

    std::string name;
    std::string hexCode;

    Colour() = default;

    Colour(std::string name, std::string hexCode, int wheelIndex);

    bool operator==(const Colour& otherString) const
    {
        if (this->name == otherString.name)
        {
            return true;
        }

        return false;
    }
};

#endif // COLOUR_H

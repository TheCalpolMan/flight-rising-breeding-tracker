#ifndef COLOUR_H
#define COLOUR_H

#include <string>

struct Colour
{
public:
    int wheelIndex;

    std::string name;
    std::string hexCode;

    Colour(std::string name, std::string hexCode, int wheelIndex);
};

#endif // COLOUR_H

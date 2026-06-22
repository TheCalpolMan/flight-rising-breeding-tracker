#ifndef COLOUR_H
#define COLOUR_H

#include <string>

struct Colour
{
public:
    std::string name;
    std::string hexCode;

    Colour(std::string name, std::string hexCode);
};

#endif // COLOUR_H

#include "colour.h"

Colour::Colour(std::string name, std::string hexCode, int wheelIndex)
{
    this->name = name;
    this->hexCode = hexCode;
    this->wheelIndex = wheelIndex;
}

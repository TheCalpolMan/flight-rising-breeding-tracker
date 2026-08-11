#include "dragonregex.h"

#include <sstream>
#include <iostream>


#include "information.h"

Dragon DragonRegex::ConstructDragon(const std::string &paste)
{
    Dragon dragon;

    // std::regex name = std::regex("[^\\s]+\\s*\\(#\\d+\\)",
    //     std::regex_constants::extended);

    std::string breedGenderString = "icon\\s*((Female)?(Male)?)\\s*(" + getConcatenatedDragonBreeds() + ")";
    // std::cout << paste << std::endl;

    // re2::RE2::FullMatch("hello", "h.*o");

    std::cout << std::endl;

    return dragon;
}

std::string DragonRegex::getConcatenatedDragonBreeds()
{
    std::stringstream stream;

    for (const auto& breed : Information::getInstance().getBreeds())
    {
        stream << "(" << breed.string << ")?";
    }

    return stream.str();
}

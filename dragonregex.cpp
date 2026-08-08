#include "dragonregex.h"

#include <regex>
#include <sstream>
#include <iostream>

#include "information.h"

Dragon DragonRegex::ConstructDragon(const std::string &paste)
{
    Dragon dragon;

    std::regex name = std::regex("[^\\s]+\\s*\\(#\\d+\\)",
        std::regex_constants::extended);

    std::string breedGenderString = "icon\\s*((Female)?(Male)?)\\s*(" + getConcatenatedDragonBreeds() + ")";
    // std::cout << paste << std::endl;
    std::regex breedGender = std::regex(breedGenderString,
        std::regex_constants::extended);

    std::smatch matches;

    bool matched = std::regex_search(paste, matches, name);

    for (std::size_t i = 0; i < matches.size(); ++i)
        std::cout << i << ": " << matches[i] << '\n';

    matched = std::regex_search(paste, matches, breedGender);

    for (std::size_t i = 0; i < matches.size(); ++i)
        std::cout << i << ": " << matches[i] << '\n';

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

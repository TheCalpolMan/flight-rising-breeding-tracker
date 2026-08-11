#include "dragonregex.h"

#include <sstream>
#include <iostream>

#include "re2/re2/re2.h"

#include "information.h"

Dragon DragonRegex::ConstructDragon(const std::string &paste)
{
    Dragon dragon;

    // std::regex name = std::regex("[^\\s]+\\s*\\(#\\d+\\)",
    //     std::regex_constants::extended);

    std::string breedGenderString = "icon\\s*((Female)?(Male)?)\\s*(" + getConcatenatedDragonBreeds() + ")";
    // std::cout << paste << std::endl;

    int i;
    std::string s;
    assert(RE2::FullMatch("ruby:1234", "(\\w+):(\\d+)", &s, &i));
    assert(s == "ruby");
    assert(i == 1234);

    // std::cout << "Joined string: " << s << std::endl;

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

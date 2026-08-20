#include "colour.h"

#include <cmath>

Colour::Colour(std::string name, std::string hexCode, int wheelIndex)
{
    this->name = name;
    this->hexCode = hexCode;
    this->wheelIndex = wheelIndex;
}

int Colour::convertHexadecimal(std::string hex)
{
    int value = 0;

    int power = 0;
    for (auto it = hex.rbegin(); it != hex.rend(); it++)
    {
        char character = *it;

        if (character <= '9')
        {
            character = character - '0';
        }
        else if (character <= 'Z')
        {
            character = character - 'A' + 10;
        }
        else
        {
            character = character - 'a' + 10;
        }

        value += std::pow(16, power) * character;
        power++;
    }

    return value;
}

Colour::HSL Colour::toHsl() const
{
    HSL hsl;

    // using algorithm from https://www.rapidtables.com/convert/color/rgb-to-hsl.html

    float red = convertHexadecimal(hexCode.substr(1, 2)) / 255.0;
    float green = convertHexadecimal(hexCode.substr(3, 2)) / 255.0;
    float blue = convertHexadecimal(hexCode.substr(5, 2)) / 255.0;

    float cMax = std::max(std::max(red, green), blue);
    float cMin = std::min(std::min(red, green), blue);

    float delta = cMax - cMin;

    if (delta == 0)
    {
        hsl.hue = 0;
    }
    else if (cMax == red)
    {
        hsl.hue = 3.1415 / 3.0 * std::fmod((green - blue) / delta, 6);
    }
    else if (cMax == green)
    {
        hsl.hue = 3.1415 / 3.0 * ((blue - red) / delta + 2);
    }
    else
    {
        hsl.hue = 3.1415 / 3.0 * ((red - green) / delta + 4);
    }

    hsl.lightness = (cMax + cMin) / 2.0;

    if (delta == 0)
    {
        hsl.saturation = 0;
    }
    else
    {
        hsl.saturation = delta / (1 - std::fabs(2 * hsl.lightness - 1));
    }

    return hsl;
}

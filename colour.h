#ifndef COLOUR_H
#define COLOUR_H

#include <string>

class Colour
{
public:
    struct HSL
    {
        float hue;
        float saturation;
        float lightness;
    };

    int wheelIndex;

    std::string name;
    std::string hexCode;

    Colour() = default;

    Colour(std::string name, std::string hexCode, int wheelIndex);

    bool operator==(const Colour& other) const
    {
        if (this->name == other.name)
        {
            return true;
        }

        return false;
    }

    HSL toHsl() const;
private:
    static int convertHexadecimal(std::string hex);
};

#endif // COLOUR_H

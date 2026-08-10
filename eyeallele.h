#ifndef EYEALLELE_H
#define EYEALLELE_H

#include <string>

struct EyeAllele
{
public:
    std::string string;
    int weighting;

    EyeAllele() = default;

    EyeAllele(std::string string, int weighting);

    bool operator==(const EyeAllele& other) const
    {
        if (this->string == other.string)
        {
            return true;
        }

        return false;
    }
};

#endif // EYEALLELE_H

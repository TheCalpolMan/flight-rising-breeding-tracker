#ifndef EYEALLELE_H
#define EYEALLELE_H

#include <string>

struct EyeAllele
{
public:
    int weighting;
    std::string string;

    EyeAllele() = default;

    EyeAllele(int weighting, std::string string);

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

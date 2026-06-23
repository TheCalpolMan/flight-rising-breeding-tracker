#ifndef EYEALLELE_H
#define EYEALLELE_H

#include <string>

struct EyeAllele
{
public:
    int weighting;
    std::string string;

    EyeAllele(int weighting, std::string string);
};

#endif // EYEALLELE_H

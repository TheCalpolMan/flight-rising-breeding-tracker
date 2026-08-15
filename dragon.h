#ifndef DRAGON_H
#define DRAGON_H

#include <memory>
#include <vector>

#include "colour.h"
#include "allele.h"
#include "eyeallele.h"

struct Dragon
{
public:
    std::vector<std::pair<int, std::weak_ptr<Dragon>>> lineage = decltype(lineage)();

    bool male = false;
    Allele breed;
    EyeAllele eye;

    Colour primaryColour;
    Colour secondaryColour;
    Colour tertiaryColour;

    Allele primaryGene;
    Allele secondaryGene;
    Allele tertiaryGene;

    std::string name = "";
    std::string imageLocation = "";

    int id = -1;

    Dragon() = default;

    Dragon(const std::string& name, bool male, const EyeAllele& eye, const Allele& breed,
       const Colour& primaryColour, const Colour& secondaryColour, const Colour& tertiaryColour,
       const Allele& primaryGene, const Allele& secondaryGene, const Allele& tertiaryGene);

    void addLineage(int generation, std::shared_ptr<Dragon> progenitor);

    bool removeLineage(std::shared_ptr<Dragon> progenitor);

    std::pair<int, std::weak_ptr<Dragon>> isDragonRelated(const std::shared_ptr<Dragon> potentialRelative);

    std::pair<int, std::weak_ptr<Dragon>> isDragonTransitivelyRelated(const std::shared_ptr<Dragon> potentialRelative);
};

#endif // DRAGON_H

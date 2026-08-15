#include "dragon.h"

Dragon::Dragon(const std::string& name, bool male, const EyeAllele& eye, const Allele& breed,
    const Colour& primaryColour, const Colour& secondaryColour, const Colour& tertiaryColour,
    const Allele& primaryGene, const Allele& secondaryGene, const Allele& tertiaryGene) :
    name(name),
    male(male),
    eye(eye),
    breed(breed),
    primaryColour(primaryColour),
    secondaryColour(secondaryColour),
    tertiaryColour(tertiaryColour),
    primaryGene(primaryGene),
    secondaryGene(secondaryGene),
    tertiaryGene(tertiaryGene)
{

}

void Dragon::addLineage(int generation, std::shared_ptr<Dragon> progenitor)
{
    lineage.emplace_back(generation, std::weak_ptr<Dragon>(progenitor));
}

bool Dragon::removeLineage(std::shared_ptr<Dragon> progenitor)
{
    for (int i = 0; i < lineage.size(); i++)
    {
        const auto& relation = lineage.at(i);

        if (relation.second.expired())
        {
            continue;
        }

        if (relation.second.lock() == progenitor)
        {
            lineage.erase(lineage.cbegin() + i);
            return true;
        }
    }

    return false;
}

std::pair<int, std::weak_ptr<Dragon>> Dragon::isDragonRelated(const std::shared_ptr<Dragon> potentialRelative)
{
    for (const auto& relation : lineage)
    {
        if (relation.second.expired())
        {
            continue;
        }

        if (relation.second.lock() == potentialRelative)
        {
            return relation;
        }
    }

    return std::make_pair<int, std::weak_ptr<Dragon>>(-1, std::weak_ptr<Dragon>());
}

std::pair<int, std::weak_ptr<Dragon>> Dragon::isDragonTransitivelyRelated(const std::shared_ptr<Dragon> potentialRelative)
{
    for (const auto& relation : lineage)
    {
        if (relation.second.expired())
        {
            continue;
        }

        if (relation.second.lock() == potentialRelative)
        {
            return relation;
        }

        auto transitiveRelation = relation.second.lock()->isDragonTransitivelyRelated(potentialRelative);

        if (transitiveRelation.first != -1)
        {
            return std::make_pair(relation.first + transitiveRelation.first + 1, transitiveRelation.second);
        }
    }

    return std::make_pair<int, std::weak_ptr<Dragon>>(-1, std::weak_ptr<Dragon>());
}

#include "information.h"

#include <algorithm>

Information::Information()
{
    // eyes
    {
        eyes.push_back(Allele(Rarity::Plentiful, "Common"));
    }

    // breeds
    {
        breeds.push_back(Allele(Rarity::Plentiful, "Fae"));
        breeds.push_back(Allele(Rarity::Plentiful, "Guardian"));
        breeds.push_back(Allele(Rarity::Plentiful, "Mirror"));
        breeds.push_back(Allele(Rarity::Common, "Pearlcatcher"));
        breeds.push_back(Allele(Rarity::Common, "Ridgeback"));
        breeds.push_back(Allele(Rarity::Plentiful, "Tundra"));
        breeds.push_back(Allele(Rarity::Common, "Spiral"));
        breeds.push_back(Allele(Rarity::Limited, "Imperial"));
        breeds.push_back(Allele(Rarity::Common, "Snapper"));
        breeds.push_back(Allele(Rarity::Rare, "Wildclaw"));
        breeds.push_back(Allele(Rarity::Limited, "Nocturne"));
        breeds.push_back(Allele(Rarity::Rare, "Coatl"));
        breeds.push_back(Allele(Rarity::Uncommon, "Skydancer"));
        breeds.push_back(Allele(Rarity::Uncommon, "Bogsneak"));
        breeds.push_back(Allele(Rarity::Uncommon, "Obelisk"));
        breeds.push_back(Allele(Rarity::Uncommon, "Fathom"));
        breeds.push_back(Allele(Rarity::Ancient, "Gaoler", "Gaoler"));
        breeds.push_back(Allele(Rarity::Ancient, "Banescale", "Banescale"));
        breeds.push_back(Allele(Rarity::Ancient, "Veilspun", "Veilspun"));
        breeds.push_back(Allele(Rarity::Ancient, "Aberration", "Aberration"));
        breeds.push_back(Allele(Rarity::Ancient, "Undertide", "Undertide"));
        breeds.push_back(Allele(Rarity::Ancient, "Aether", "Aether"));
        breeds.push_back(Allele(Rarity::Ancient, "Sandsurge", "Sandsurge"));
        breeds.push_back(Allele(Rarity::Ancient, "Auraboa", "Auraboa"));
        breeds.push_back(Allele(Rarity::Ancient, "Dusthide", "Dusthide"));
        breeds.push_back(Allele(Rarity::Ancient, "Everlux", "Everlux"));
        breeds.push_back(Allele(Rarity::Ancient, "Cirrus", "Cirrus"));
        breeds.push_back(Allele(Rarity::Ancient, "Vigil", "Vigil"));
        breeds.push_back(Allele(Rarity::Ancient, "Thorntail", "Thorntail"));
    }

    // primary genes
    {
        primaryGenes.push_back(Allele(Rarity::Plentiful, "Basic"));

        primaryGenes.push_back(Allele(Rarity::Common, "Checkers"));
        primaryGenes.push_back(Allele(Rarity::Common, "Clown"));
        primaryGenes.push_back(Allele(Rarity::Common, "Fade"));
        primaryGenes.push_back(Allele(Rarity::Common, "Falcon"));
        primaryGenes.push_back(Allele(Rarity::Common, "Laced"));
        primaryGenes.push_back(Allele(Rarity::Common, "Leopard"));
        primaryGenes.push_back(Allele(Rarity::Common, "Piebald"));
        primaryGenes.push_back(Allele(Rarity::Common, "Savannah"));
        primaryGenes.push_back(Allele(Rarity::Common, "Speckle"));
        primaryGenes.push_back(Allele(Rarity::Common, "Swirl"));
        primaryGenes.push_back(Allele(Rarity::Common, "Tapir"));
        primaryGenes.push_back(Allele(Rarity::Common, "Tiger"));
        primaryGenes.push_back(Allele(Rarity::Common, "Varnish"));

        primaryGenes.push_back(Allele(Rarity::Uncommon, "Bar"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Boa"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Cherub"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Chorus"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Cinder"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Flaunt"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Giraffe"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Jaguar"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Jupiter"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Lionfish"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Mosaic"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Ragged"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Ribbon"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Ripple"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Sphinxmoth"));
        primaryGenes.push_back(Allele(Rarity::Uncommon, "Vipera"));

        primaryGenes.push_back(Allele(Rarity::Limited, "Boulder"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Chrysocolla"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Fern"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Ground"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Love"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Pinstripe"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Orb"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Poison"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Python"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Sailfish"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Skink"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Slime"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Soil"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Stitched"));
        primaryGenes.push_back(Allele(Rarity::Limited, "Tide"));

        primaryGenes.push_back(Allele(Rarity::Rare, "Crystal"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Harlequin"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Iridescent"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Metallic"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Petals"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Petrified"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Pharaoh"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Starmap"));
        primaryGenes.push_back(Allele(Rarity::Rare, "Wasp"));
    }

    // secondary genes
    {
        secondaryGenes.push_back(Allele(Rarity::Plentiful, "Basic"));

        secondaryGenes.push_back(Allele(Rarity::Common, "Blend"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Chess"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Clouded"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Edged"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Eye Spots"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Freckle"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Lacquer"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Marbled"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Paint"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Peregrine"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Safari"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Striation"));
        secondaryGenes.push_back(Allele(Rarity::Common, "Stripes"));

        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Blaze"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Breakup"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Choir"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Current"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Daub"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Eel"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Flair"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Hawkmoth"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Hex"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Hypnotic"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Noxtide"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Rosette"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Saddle"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Saturn"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Seraph"));
        secondaryGenes.push_back(Allele(Rarity::Uncommon, "Tear"));

        secondaryGenes.push_back(Allele(Rarity::Limited, "Affection"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Fissure"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Foam"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Loam"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Malachite"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Marlin"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Morph"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Myrid"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Paisley"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Patchwork"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Sludge"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Spinner"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Toxin"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Trail"));
        secondaryGenes.push_back(Allele(Rarity::Limited, "Weaver"));

        secondaryGenes.push_back(Allele(Rarity::Rare, "Alloy"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Bee"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Butterfly"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Constellation"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Facet"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Jester"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Lode"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Sarcopagus"));
        secondaryGenes.push_back(Allele(Rarity::Rare, "Shimmer"));
    }

    // tertiary genes
    {
        tertiaryGenes.push_back(Allele(Rarity::Plentiful, "Basic"));

        tertiaryGenes.push_back(Allele(Rarity::Common, "Contour"));
        tertiaryGenes.push_back(Allele(Rarity::Common, "Darts"));
        tertiaryGenes.push_back(Allele(Rarity::Common, "Peacock"));
        tertiaryGenes.push_back(Allele(Rarity::Common, "Points"));
        tertiaryGenes.push_back(Allele(Rarity::Common, "Thylacine"));
        tertiaryGenes.push_back(Allele(Rarity::Common, "Underbelly"));

        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Crackle"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Gecko"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Gembond"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Ghost"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Lace"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Okapi"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Ringlets"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Runes"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Smoke"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Sparkle"));
        tertiaryGenes.push_back(Allele(Rarity::Uncommon, "Spines"));

        tertiaryGenes.push_back(Allele(Rarity::Limited, "Capsule"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Firebreather"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Firefly"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Flecks"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Keel"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Magpie"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Polkadot"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Scales"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Smirch"));
        tertiaryGenes.push_back(Allele(Rarity::Limited, "Veined"));

        tertiaryGenes.push_back(Allele(Rarity::Rare, "Circuit"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Eclipse"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Filigree"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Glimmer"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Glowtail"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Koi"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Opal"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Soap"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Stained"));
        tertiaryGenes.push_back(Allele(Rarity::Rare, "Wish"));
    }

    // Colours
    {
        colours.push_back(Colour("Antique", "#D8D6CD", 2));
        colours.push_back(Colour("White", "#FFFFFF", 3));
        colours.push_back(Colour("Moon", "#D8D7D8", 4));
        colours.push_back(Colour("Maize", "#FFFDEA", 0));
        colours.push_back(Colour("Cream", "#FFEFDC", 1));

        coloursByWheel = colours;
        std::sort(coloursByWheel.begin(), coloursByWheel.end(),
            [](const Colour& a, const Colour& b)
            {
                return a.wheelIndex < b.wheelIndex;
            }
        );
    }
}

const std::vector<Allele>& Information::getEyes() const
{
    return eyes;
}

const std::vector<Allele>& Information::getBreeds() const
{
    return breeds;
}

const std::vector<Allele>& Information::getPrimaryGenes() const
{
    return primaryGenes;
}

const std::vector<Allele>& Information::getSecondaryGenes() const
{
    return secondaryGenes;
}

const std::vector<Allele>& Information::getTertiaryGenes() const
{
    return tertiaryGenes;
}

const std::vector<Colour>& Information::getColours(bool sortByWheel) const
{
    if (!sortByWheel)
    {
        return colours;
    }

    return coloursByWheel;
}

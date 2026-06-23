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
        colours.push_back(Colour("Maize", "#FFFDEA", 1));
        colours.push_back(Colour("Cream", "#FFEFDC", 2));
        colours.push_back(Colour("Antique", "#D8D6CD", 3));
        colours.push_back(Colour("White", "#FFFFFF", 4));
        colours.push_back(Colour("Moon", "#D8D7D8", 5));
        colours.push_back(Colour("Ice", "#F1F3FF", 6));
        colours.push_back(Colour("Orca", "#E1DFFF", 7));
        colours.push_back(Colour("Platinum", "#C8BECE", 8));
        colours.push_back(Colour("Silver", "#BBBABF", 9));
        colours.push_back(Colour("Dust", "#9D9D9F", 10));
        colours.push_back(Colour("Grey", "#808080", 11));
        colours.push_back(Colour("Smoke", "#9494A9", 12));
        colours.push_back(Colour("Gloom", "#545365", 13));
        colours.push_back(Colour("Lead", "#413C40", 14));
        colours.push_back(Colour("Shale", "#4D484F", 15));
        colours.push_back(Colour("Flint", "#636268", 16));
        colours.push_back(Colour("Charcoal", "#555555", 17));
        colours.push_back(Colour("Coal", "#4B4946", 18));
        colours.push_back(Colour("Oilslick", "#352C27", 19));
        colours.push_back(Colour("Black", "#333333", 20));
        colours.push_back(Colour("Obsidian", "#1D2224", 21));
        colours.push_back(Colour("Eldritch", "#252A24", 22));
        colours.push_back(Colour("Midnight", "#292B38", 23));
        colours.push_back(Colour("Shadow", "#3A2E44", 24));
        colours.push_back(Colour("Blackberry", "#4C2A4F", 25));
        colours.push_back(Colour("Mulberry", "#6E235D", 26));
        colours.push_back(Colour("Plum", "#863290", 27));
        colours.push_back(Colour("Wisteria", "#724D79", 28));
        colours.push_back(Colour("Thistle", "#8F7C8B", 29));
        colours.push_back(Colour("Fog", "#A794B2", 30));
        colours.push_back(Colour("Mist", "#E1CDFE", 31));
        colours.push_back(Colour("Lavender", "#CCA4E0", 32));
        colours.push_back(Colour("Heather", "#9778BE", 33));
        colours.push_back(Colour("Purple", "#A261CF", 34));
        colours.push_back(Colour("Orchid", "#DA4FFF", 35));
        colours.push_back(Colour("Amethyst", "#993BD1", 36));
        colours.push_back(Colour("Nightshade", "#7930B5", 37));
        colours.push_back(Colour("Violet", "#643F9C", 38));
        colours.push_back(Colour("Grape", "#580FC0", 39));
        colours.push_back(Colour("Royal", "#4D2C89", 40));
        colours.push_back(Colour("Eggplant", "#3F2B66", 41));
        colours.push_back(Colour("Iris", "#525195", 42));
        colours.push_back(Colour("Storm", "#757ADB", 43));
        colours.push_back(Colour("Twilight", "#484AA1", 44));
        colours.push_back(Colour("Indigo", "#2D237A", 45));
        colours.push_back(Colour("Sapphire", "#0D0A5B", 46));
        colours.push_back(Colour("Navy", "#212B5F", 47));
        colours.push_back(Colour("Cobalt", "#013485", 48));
        colours.push_back(Colour("Ultramarine", "#1C51E7", 49));
        colours.push_back(Colour("Blue", "#324BA9", 50));
        colours.push_back(Colour("Periwinkle", "#4866D5", 51));
        colours.push_back(Colour("Lapis", "#2F83FF", 52));
        colours.push_back(Colour("Splash", "#6394DD", 53));
        colours.push_back(Colour("Cornflower", "#76A8FF", 54));
        colours.push_back(Colour("Sky", "#AEC8FF", 55));
        colours.push_back(Colour("Stonewash", "#7895C1", 56));
        colours.push_back(Colour("Overcast", "#444F69", 57));
        colours.push_back(Colour("Steel", "#556979", 58));
        colours.push_back(Colour("Denim", "#2F4557", 59));
        colours.push_back(Colour("Abyss", "#0D1E25", 60));
        colours.push_back(Colour("Phthalo", "#0B2D46", 61));
        colours.push_back(Colour("Azure", "#0A3D67", 62));
        colours.push_back(Colour("Caribbean", "#0086CE", 63));
        colours.push_back(Colour("Teal", "#2B768F", 64));
        colours.push_back(Colour("Cerulean", "#00B4D5", 65));
        colours.push_back(Colour("Cyan", "#00FFF1", 66));
        colours.push_back(Colour("Robin", "#9AEAEF", 67));
        colours.push_back(Colour("Aqua", "#72C4C4", 68));
        colours.push_back(Colour("Turquoise", "#3CA2A4", 69));
        colours.push_back(Colour("Spruce", "#8DBCB4", 70));
        colours.push_back(Colour("Pistachio", "#E2FFE6", 71));
        colours.push_back(Colour("Seafoam", "#B2E2BD", 72));
        colours.push_back(Colour("Mint", "#9AFFC7", 73));
        colours.push_back(Colour("Jade", "#61AB89", 74));
        colours.push_back(Colour("Spearmint", "#148E67", 75));
        colours.push_back(Colour("Thicket", "#005D48", 76));
        colours.push_back(Colour("Peacock", "#1F483A", 77));
        colours.push_back(Colour("Emerald", "#20603F", 78));
        colours.push_back(Colour("Shamrock", "#236825", 79));
        colours.push_back(Colour("Jungle", "#1E361A", 80));
        colours.push_back(Colour("Hunter", "#1E2716", 81));
        colours.push_back(Colour("Forest", "#425035", 82));
        colours.push_back(Colour("Camo", "#51684C", 83));
        colours.push_back(Colour("Algae", "#97AF8B", 84));
        colours.push_back(Colour("Swamp", "#687F67", 85));
        colours.push_back(Colour("Avocado", "#567C34", 86));
        colours.push_back(Colour("Green", "#629C3F", 87));
        colours.push_back(Colour("Fern", "#7ECE73", 88));
        colours.push_back(Colour("Mantis", "#9BFF9D", 89));
        colours.push_back(Colour("Pear", "#8ECE56", 90));
        colours.push_back(Colour("Leaf", "#A5E32D", 91));
        colours.push_back(Colour("Radioactive", "#C6FF00", 92));
        colours.push_back(Colour("Honeydew", "#D1E572", 93));
        colours.push_back(Colour("Peridot", "#E8FCB4", 94));
        colours.push_back(Colour("Chartreuse", "#B4CD3D", 95));
        colours.push_back(Colour("Spring", "#A9A032", 96));
        colours.push_back(Colour("Crocodile", "#828335", 97));
        colours.push_back(Colour("Olive", "#697135", 98));
        colours.push_back(Colour("Murk", "#4B4420", 99));
        colours.push_back(Colour("Moss", "#7E7645", 100));
        colours.push_back(Colour("Goldenrod", "#BEA55D", 101));
        colours.push_back(Colour("Amber", "#C18E1B", 102));
        colours.push_back(Colour("Honey", "#D1B300", 103));
        colours.push_back(Colour("Lemon", "#FFE63B", 104));
        colours.push_back(Colour("Yellow", "#F9E255", 105));
        colours.push_back(Colour("Grapefruit", "#F7FF6F", 106));
        colours.push_back(Colour("Banana", "#FFEC80", 107));
        colours.push_back(Colour("Sanddollar", "#EDE8B0", 108));
        colours.push_back(Colour("Flaxen", "#FDE9AC", 109));
        colours.push_back(Colour("Ivory", "#FFD297", 110));
        colours.push_back(Colour("Buttercup", "#F6BF6C", 111));
        colours.push_back(Colour("Gold", "#E8AF49", 112));
        colours.push_back(Colour("Metals", "#D1B045", 113));
        colours.push_back(Colour("Marigold", "#FFB53C", 114));
        colours.push_back(Colour("Sunshine", "#FA912B", 115));
        colours.push_back(Colour("Saffron", "#FF8500", 116));
        colours.push_back(Colour("Sunset", "#FFA147", 117));
        colours.push_back(Colour("Peach", "#FFB576", 118));
        colours.push_back(Colour("Cantaloupe", "#FF984F", 119));
        colours.push_back(Colour("Orange", "#D5602B", 120));
        colours.push_back(Colour("Bronze", "#B2560D", 121));
        colours.push_back(Colour("Terracotta", "#B24407", 122));
        colours.push_back(Colour("Carrot", "#FF5500", 123));
        colours.push_back(Colour("Fire", "#EF5C23", 124));
        colours.push_back(Colour("Pumpkin", "#FF6841", 125));
        colours.push_back(Colour("Tangerine", "#FF7360", 126));
        colours.push_back(Colour("Cinnamon", "#C15A39", 127));
        colours.push_back(Colour("Caramel", "#C47149", 128));
        colours.push_back(Colour("Sand", "#B27749", 129));
        colours.push_back(Colour("Tan", "#C3996F", 130));
        colours.push_back(Colour("Beige", "#CABBA2", 131));
        colours.push_back(Colour("Stone", "#827A64", 132));
        colours.push_back(Colour("Taupe", "#6D675B", 133));
        colours.push_back(Colour("Slate", "#564D48", 134));
        colours.push_back(Colour("Driftwood", "#766259", 135));
        colours.push_back(Colour("Latte", "#977B6C", 136));
        colours.push_back(Colour("Dirt", "#774840", 137));
        colours.push_back(Colour("Clay", "#603E3D", 138));
        colours.push_back(Colour("Sable", "#57372C", 139));
        colours.push_back(Colour("Umber", "#301E1A", 140));
        colours.push_back(Colour("Soil", "#5A4534", 141));
        colours.push_back(Colour("Hickory", "#72573A", 142));
        colours.push_back(Colour("Tarnish", "#855B33", 143));
        colours.push_back(Colour("Ginger", "#91532A", 144));
        colours.push_back(Colour("Brown", "#8E5B3F", 145));
        colours.push_back(Colour("Chocolate", "#563012", 146));
        colours.push_back(Colour("Auburn", "#7B3C1D", 147));
        colours.push_back(Colour("Copper", "#A44B28", 148));
        colours.push_back(Colour("Rust", "#8B3220", 149));
        colours.push_back(Colour("Tomato", "#BA311C", 150));
        colours.push_back(Colour("Vermilion", "#E22D18", 151));
        colours.push_back(Colour("Ruby", "#CE000D", 152));
        colours.push_back(Colour("Cherry", "#AA0024", 153));
        colours.push_back(Colour("Crimson", "#850012", 154));
        colours.push_back(Colour("Garnet", "#581014", 155));
        colours.push_back(Colour("Sanguine", "#2D0102", 156));
        colours.push_back(Colour("Blood", "#451717", 157));
        colours.push_back(Colour("Maroon", "#652127", 158));
        colours.push_back(Colour("Berry", "#8C272D", 159));
        colours.push_back(Colour("Red", "#C1272D", 160));
        colours.push_back(Colour("Strawberry", "#DF3236", 161));
        colours.push_back(Colour("Cerise", "#A12928", 162));
        colours.push_back(Colour("Carmine", "#B13A3A", 163));
        colours.push_back(Colour("Brick", "#9A534D", 164));
        colours.push_back(Colour("Coral", "#CC6F6F", 165));
        colours.push_back(Colour("Blush", "#FEA0A0", 166));
        colours.push_back(Colour("Cottoncandy", "#EB799A", 167));
        colours.push_back(Colour("Watermelon", "#DB518D", 168));
        colours.push_back(Colour("Magenta", "#E934AA", 169));
        colours.push_back(Colour("Fuchsia", "#E7008B", 170));
        colours.push_back(Colour("Raspberry", "#8A024A", 171));
        colours.push_back(Colour("Wine", "#4D0F28", 172));
        colours.push_back(Colour("Mauve", "#9C4975", 173));
        colours.push_back(Colour("Pink", "#E77FBF", 174));
        colours.push_back(Colour("Bubblegum", "#E5A9FF", 175));
        colours.push_back(Colour("Rose", "#FFD6F6", 176));
        colours.push_back(Colour("Pearl", "#FBEDFA", 177));

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

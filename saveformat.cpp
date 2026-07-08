#include "saveformat.h"

#include <fstream>

#include <document.h>
#include <stringbuffer.h>
#include <prettywriter.h>

#include "information.h"
#include "vectorhelpers.h"

const std::string SaveFormat::ending = ".json";

SaveFormat::SaveFormat(const Dragon& dragon, bool primaryToggle, bool secondaryToggle, bool tertiaryToggle,
           bool breedToggle, int primaryColourRange, int primaryColourOffset, int secondaryColourRange,
           int secondaryColourOffset, int tertiaryColourRange, int tertiaryColourOffset) :
    dragon(dragon),
    primaryToggle(primaryToggle),
    secondaryToggle(secondaryToggle),
    tertiaryToggle(tertiaryToggle),
    breedToggle(breedToggle),
    primaryColourRange(primaryColourRange),
    primaryColourOffset(primaryColourOffset),
    secondaryColourRange(secondaryColourRange),
    secondaryColourOffset(secondaryColourOffset),
    tertiaryColourRange(tertiaryColourRange),
    tertiaryColourOffset(tertiaryColourOffset)
{

}
SaveFormat::SaveFormat(const std::string& fileLocation)
{

}

void SaveFormat::write(const std::string& fileLocation)
{
    // Source - https://stackoverflow.com/a/22855935
    // Posted by ArtemGr, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-07-08, License - CC BY-SA 3.0
    // modified heavily in line with https://gist.github.com/fclairamb/0d03cf713985100ccd51

    rapidjson::Document document;
    document.SetObject();
    auto& allocator = document.GetAllocator();

    rapidjson::Value jsonString;
    const auto& information = Information::getInstance();

    {
        rapidjson::Value morphology(rapidjson::kObjectType);

        {
            rapidjson::Value dragon(rapidjson::kObjectType);

            dragon.AddMember("family", -1, allocator);

            jsonString.SetString(this->dragon.breed.string.c_str(), allocator);
            dragon.AddMember("breed", jsonString, allocator);

            jsonString.SetString(this->dragon.eye.string.c_str(), allocator);
            dragon.AddMember("eye", jsonString, allocator);

            {
                rapidjson::Value primary(rapidjson::kObjectType);

                primary.AddMember("colour", VectorHelpers::getIndex(information.getColours(false), this->dragon.primaryColour), allocator);
                primary.AddMember("gene", VectorHelpers::getIndex(information.getPrimaryGenes(), this->dragon.primaryGene), allocator);

                dragon.AddMember("primary", primary, allocator);
            }

            {
                rapidjson::Value secondary(rapidjson::kObjectType);

                secondary.AddMember("colour", VectorHelpers::getIndex(information.getColours(false), this->dragon.secondaryColour), allocator);
                secondary.AddMember("gene", VectorHelpers::getIndex(information.getSecondaryGenes(), this->dragon.secondaryGene), allocator);

                dragon.AddMember("secondary", secondary, allocator);
            }

            {
                rapidjson::Value tertiary(rapidjson::kObjectType);

                tertiary.AddMember("colour", VectorHelpers::getIndex(information.getColours(false), this->dragon.tertiaryColour), allocator);
                tertiary.AddMember("gene", VectorHelpers::getIndex(information.getTertiaryGenes(), this->dragon.tertiaryGene), allocator);

                dragon.AddMember("tertiary", tertiary, allocator);
            }

            morphology.AddMember("dragon", dragon, allocator);
        }

        jsonString.SetString(dragon.imageLocation.c_str(), allocator);
        morphology.AddMember("image", jsonString, allocator);

        document.AddMember("morphology", morphology, allocator);
    }

    {
        rapidjson::Value search(rapidjson::kObjectType);

        {
            rapidjson::Value toggles(rapidjson::kObjectType);

            toggles.AddMember("primary", primaryToggle, allocator);
            toggles.AddMember("secondary", secondaryToggle, allocator);
            toggles.AddMember("tertiary", tertiaryToggle, allocator);
            toggles.AddMember("breed", breedToggle, allocator);

            search.AddMember("toggles", toggles, allocator);
        }

        {
            rapidjson::Value primary(rapidjson::kObjectType);

            primary.AddMember("range", primaryColourRange, allocator);
            primary.AddMember("offset", primaryColourOffset, allocator);

            search.AddMember("primary", primary, allocator);
        }

        {
            rapidjson::Value secondary(rapidjson::kObjectType);

            secondary.AddMember("range", secondaryColourRange, allocator);
            secondary.AddMember("offset", secondaryColourOffset, allocator);

            search.AddMember("secondary", secondary, allocator);
        }

        {
            rapidjson::Value tertiary(rapidjson::kObjectType);

            tertiary.AddMember("range", tertiaryColourRange, allocator);
            tertiary.AddMember("offset", tertiaryColourOffset, allocator);

            search.AddMember("tertiary", tertiary, allocator);
        }

        document.AddMember("search", search, allocator);
    }

    rapidjson::StringBuffer buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
    document.Accept (writer);
    std::string json (buf.GetString(), buf.GetSize());

    std::ofstream of (fileLocation + ending);
    of << json;
    if (!of.good()) throw std::runtime_error ("Can't write the JSON string to the file!");
}

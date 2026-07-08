#include "saveformat.h"

#include <fstream>
#include <stdexcept>
#include <filesystem>

#include <schema.h>
#include <document.h>
#include <stringbuffer.h>
#include <prettywriter.h>
#include <istreamwrapper.h>

#include "information.h"
#include "vectorhelpers.h"

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
    if (!std::filesystem::exists(fileLocation))
    {
        throw std::invalid_argument("File does not exist");
    }

    rapidjson::Document schema;

    {
        std::ifstream fStream("./assets/save-schema.json");
        rapidjson::IStreamWrapper iStreamWrapper(fStream);

        schema.ParseStream(iStreamWrapper);
    }

    rapidjson::SchemaDocument schemaDocument(schema);
    rapidjson::SchemaValidator validator(schemaDocument);

    rapidjson::Document document;
    {
        std::ifstream fStream(fileLocation);
        rapidjson::IStreamWrapper iStreamWrapper(fStream);

        document.ParseStream(iStreamWrapper);
    }

    if (!document.Accept(validator))
    {
        throw std::invalid_argument("File specified is not compatible with schema");
    }

    // document validated, down to (dragon) business

    const auto& information = Information::getInstance();

    dragon.family = document["morphology"]["dragon"]["family"].GetInt64();
    dragon.breed = information.getBreeds().at(document["morphology"]["dragon"]["breed"].GetInt());
    dragon.eye = information.getEyes().at(document["morphology"]["dragon"]["eye"].GetInt());

    dragon.primaryGene = information.getPrimaryGenes().at(document["morphology"]["dragon"]["primary"]["gene"].GetInt());
    dragon.secondaryGene = information.getSecondaryGenes().at(document["morphology"]["dragon"]["secondary"]["gene"].GetInt());
    dragon.tertiaryGene = information.getTertiaryGenes().at(document["morphology"]["dragon"]["tertiary"]["gene"].GetInt());

    dragon.primaryColour = information.getColours(false).at(document["morphology"]["dragon"]["primary"]["colour"].GetInt());
    dragon.secondaryColour = information.getColours(false).at(document["morphology"]["dragon"]["secondary"]["colour"].GetInt());
    dragon.tertiaryColour = information.getColours(false).at(document["morphology"]["dragon"]["tertiary"]["colour"].GetInt());

    dragon.imageLocation = document["morphology"]["dragon"]["image"].GetString();

    primaryToggle = document["search"]["toggles"]["primary"].GetBool();
    secondaryToggle = document["search"]["toggles"]["secondary"].GetBool();
    tertiaryToggle = document["search"]["toggles"]["tertiary"].GetBool();
    breedToggle = document["search"]["toggles"]["breed"].GetBool();

    primaryColourRange = document["search"]["primary"]["range"].GetInt();
    primaryColourOffset = document["search"]["primary"]["offset"].GetInt();

    secondaryColourRange = document["search"]["secondary"]["range"].GetInt();
    secondaryColourOffset = document["search"]["secondary"]["offset"].GetInt();

    tertiaryColourRange = document["search"]["tertiary"]["range"].GetInt();
    tertiaryColourOffset = document["search"]["tertiary"]["offset"].GetInt();
}

void SaveFormat::write(const std::string& fileLocation)
{
    // Source - https://stackoverflow.com/a/22855935
    // Posted by ArtemGr, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-07-08, License - CC BY-SA 3.0
    //
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
            dragon.AddMember("breed", VectorHelpers::getIndex(information.getBreeds(), this->dragon.breed), allocator);
            dragon.AddMember("eye", VectorHelpers::getIndex(information.getEyes(), this->dragon.eye), allocator);

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

            jsonString.SetString(this->dragon.imageLocation.c_str(), allocator);
            dragon.AddMember("image", jsonString, allocator);

            morphology.AddMember("dragon", dragon, allocator);
        }

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

    std::ofstream of (fileLocation);
    of << json;
    if (!of.good()) throw std::runtime_error ("Can't write the JSON string to the file!");
}

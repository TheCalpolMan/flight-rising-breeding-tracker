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
           int secondaryColourOffset, int tertiaryColourRange, int tertiaryColourOffset,
           const std::vector<Dragon>& pairingDragons) :
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
    tertiaryColourOffset(tertiaryColourOffset),
    pairingDragons(pairingDragons)
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

    dragon = readDragon(document["morphology"]["dragon"]);

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

    for (const auto& dragon : document["pairings"]["dragons"].GetArray())
    {
        pairingDragons.push_back(readDragon(dragon));
    }
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

        morphology.AddMember("dragon", writeDragon(this->dragon, allocator), allocator);

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

    {
        rapidjson::Value pairings(rapidjson::kObjectType);
        rapidjson::Value dragonList(rapidjson::kArrayType);

        for(const auto& dragon : pairingDragons)
        {
            auto dragonJson = writeDragon(dragon, allocator);

            dragonList.PushBack(dragonJson, allocator);
        }

        pairings.AddMember("dragons", dragonList, allocator);
        document.AddMember("pairings", pairings, allocator);
    }

    rapidjson::StringBuffer buf;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
    document.Accept (writer);
    std::string json (buf.GetString(), buf.GetSize());

    std::ofstream of (fileLocation);
    of << json;
    if (!of.good()) throw std::runtime_error ("Can't write the JSON string to the file!");
}

rapidjson::Value SaveFormat::writeDragon(const Dragon &dragon, rapidjson::MemoryPoolAllocator<>& allocator)
{
    const auto& information = Information::getInstance();
    rapidjson::Value dragonValue(rapidjson::kObjectType);
    rapidjson::Value jsonString;

    jsonString.SetString(dragon.name.c_str(), allocator);
    dragonValue.AddMember("name", jsonString, allocator);

    dragonValue.AddMember("family", -1, allocator);
    dragonValue.AddMember("breed", VectorHelpers::getIndex(information.getBreeds(), dragon.breed), allocator);
    dragonValue.AddMember("male", dragon.male, allocator);
    dragonValue.AddMember("eye", VectorHelpers::getIndex(information.getEyes(), dragon.eye), allocator);

    {
        rapidjson::Value primary(rapidjson::kObjectType);

        primary.AddMember("colour", VectorHelpers::getIndex(information.getColours(false), dragon.primaryColour), allocator);
        primary.AddMember("gene", VectorHelpers::getIndex(information.getPrimaryGenes(), dragon.primaryGene), allocator);

        dragonValue.AddMember("primary", primary, allocator);
    }

    {
        rapidjson::Value secondary(rapidjson::kObjectType);

        secondary.AddMember("colour", VectorHelpers::getIndex(information.getColours(false), dragon.secondaryColour), allocator);
        secondary.AddMember("gene", VectorHelpers::getIndex(information.getSecondaryGenes(), dragon.secondaryGene), allocator);

        dragonValue.AddMember("secondary", secondary, allocator);
    }

    {
        rapidjson::Value tertiary(rapidjson::kObjectType);

        tertiary.AddMember("colour", VectorHelpers::getIndex(information.getColours(false), dragon.tertiaryColour), allocator);
        tertiary.AddMember("gene", VectorHelpers::getIndex(information.getTertiaryGenes(), dragon.tertiaryGene), allocator);

        dragonValue.AddMember("tertiary", tertiary, allocator);
    }

    jsonString.SetString(dragon.imageLocation.c_str(), allocator);
    dragonValue.AddMember("image", jsonString, allocator);

    return std::move(dragonValue);
}

Dragon SaveFormat::readDragon(const rapidjson::GenericValue<rapidjson::UTF8<>>& dragonRoot)
{
    const auto& information = Information::getInstance();

    Dragon dragon;

    dragon.name = dragonRoot["name"].GetString();

    dragon.family = dragonRoot["family"].GetInt64();
    dragon.breed = information.getBreeds().at(dragonRoot["breed"].GetInt());
    dragon.male = dragonRoot["male"].GetBool();
    dragon.eye = information.getEyes().at(dragonRoot["eye"].GetInt());

    dragon.primaryGene = information.getPrimaryGenes().at(dragonRoot["primary"]["gene"].GetInt());
    dragon.secondaryGene = information.getSecondaryGenes().at(dragonRoot["secondary"]["gene"].GetInt());
    dragon.tertiaryGene = information.getTertiaryGenes().at(dragonRoot["tertiary"]["gene"].GetInt());

    dragon.primaryColour = information.getColours(false).at(dragonRoot["primary"]["colour"].GetInt());
    dragon.secondaryColour = information.getColours(false).at(dragonRoot["secondary"]["colour"].GetInt());
    dragon.tertiaryColour = information.getColours(false).at(dragonRoot["tertiary"]["colour"].GetInt());

    dragon.imageLocation = dragonRoot["image"].GetString();

    return dragon;
}

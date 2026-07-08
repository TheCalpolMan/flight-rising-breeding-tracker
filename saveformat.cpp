#include "saveformat.h"

#include <allocators.h>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>

#include <fstream>

const std::string SaveFormat::ending = ".fbt";

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

    document.AddMember("foo", 123, allocator);

    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    document.Accept (writer);
    std::string json (buf.GetString(), buf.GetSize());

    std::ofstream of (fileLocation + ending);
    of << json;
    if (!of.good()) throw std::runtime_error ("Can't write the JSON string to the file!");

}

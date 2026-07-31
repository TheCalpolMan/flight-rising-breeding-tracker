#include "csvreader.h"

#include <sstream>
#include <fstream>

CsvReader::CsvReader(const std::string& location, char delimiter)
{
    std::fstream file = std::fstream(location, std::fstream::in);

    std::stringstream currentValue;
    std::vector<std::string> currentLine = decltype(currentLine)();

    while(!file.eof())
    {
        char character = file.get();

        if (character == '#' && currentValue.str().empty() && currentLine.empty())
        {
            continue;
        }

        if (character == '\n')
        {
            currentLine.push_back(currentValue.str());

            values.push_back(currentLine);

            currentLine.clear();
            currentValue.str(std::string());

            continue;
        }

        if (character == delimiter)
        {
            currentLine.push_back(currentValue.str());

            currentValue.str(std::string());

            continue;
        }

        currentValue << character;
    }

    if (currentValue.str() != "")
    {
        currentLine.push_back(currentValue.str());
    }

    if (currentLine.size() > 0)
    {
        values.push_back(currentLine);
    }
}

const std::vector<std::vector<std::string>>& CsvReader::getValues() const
{
    return values;
}

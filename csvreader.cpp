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

        if (character == '\n')
        {
            currentLine.push_back(currentValue.str());

            values.push_back(currentLine);

            currentLine.clear();
            currentValue.clear();

            continue;
        }

        if (character == delimiter)
        {
            currentLine.push_back(currentValue.str());

            currentValue.clear();

            continue;
        }

        currentValue << character;
    }
}

const std::vector<std::vector<std::string>>& CsvReader::getValues() const
{
    return values;
}

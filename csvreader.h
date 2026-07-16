#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>

class CsvReader
{
public:
    CsvReader(const std::string& location, char delimiter = ',');

    const std::vector<std::vector<std::string>>& getValues() const;

private:
    std::vector<std::vector<std::string>> values = decltype(values)();
};

#endif // CSVREADER_H

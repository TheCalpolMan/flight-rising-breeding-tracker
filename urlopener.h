#ifndef URLOPENER_H
#define URLOPENER_H

#include <string>

class UrlOpener
{
public:
    static void openUrl(std::string url);
private:
    static void openUrlThread(std::string url);
};

#endif // URLOPENER_H

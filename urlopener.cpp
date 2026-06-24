#include "urlopener.h"

#include <thread>
#include <sstream>
#include <unordered_map>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
static const auto openUrlCommand = "start";

static const auto escapeMap = std::unordered_map<char, std::string>({
    {'&', "^&"}
});
#elif __APPLE__
static const auto openUrlCommand = "open";

static const auto escapeMap = std::unordered_map<char, std::string>({

});
#elif __linux__
static const auto openUrlCommand = "xdg-open";

static const auto escapeMap = std::unordered_map<char, std::string>({

});
#else
#error "Unknown compiler"
#endif

void UrlOpener::openUrl(std::string url)
{
    std::stringstream modifiedUrl;

    for (char character : url)
    {
        auto it = escapeMap.find(character);

        if (it == escapeMap.cend())
        {
            modifiedUrl << character;
            continue;
        }

        modifiedUrl << it->second;
    }

    auto thread = std::thread(&UrlOpener::openUrlThread, modifiedUrl.str());
    thread.detach();
}

void UrlOpener::openUrlThread(std::string url)
{
    const auto cmd = openUrlCommand + std::string(" ") + url;
    std::system(cmd.c_str());
}

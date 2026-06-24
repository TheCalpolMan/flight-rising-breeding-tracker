#include "urlopener.h"

#include <thread>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
static const auto openUrlCommand = "start";
#elif __APPLE__
static const auto openUrlCommand = "open";
#elif __linux__
static const auto openUrlCommand = "xdg-open";
#else
#error "Unknown compiler"
#endif

void UrlOpener::openUrl(std::string url)
{
    auto thread = std::thread(&UrlOpener::openUrlThread, url);
    thread.detach();
}

void UrlOpener::openUrlThread(std::string url)
{
    const auto cmd = openUrlCommand + std::string(" ") + url;
    std::system(cmd.c_str());
}

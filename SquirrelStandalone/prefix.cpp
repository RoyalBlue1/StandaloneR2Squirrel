#include <string>
#include <filesystem>
#include <spdlog/spdlog.h>
std::filesystem::path currentPrefix;

std::filesystem::path GetFilePrefix() {
    return currentPrefix;
}


void setFilePrefix(std::filesystem::path prefix){
    currentPrefix = prefix;
    //spdlog::info("Pefix set to {}", prefix.string());
}

void SetFilePrefixToCurrentDirectory() {
    currentPrefix = std::filesystem::current_path();
    //spdlog::info("Pefix set to {}", currentPrefix.string());
}
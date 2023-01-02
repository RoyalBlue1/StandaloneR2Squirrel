#include <string>
#include <filesystem>
#include <spdlog/spdlog.h>
std::filesystem::path currentPrefix;
std::filesystem::path modDir;

std::filesystem::path GetFilePrefix() {
    return currentPrefix;
}

std::filesystem::path GetModFolder() {
    return modDir;
}

void SetFilePrefix(std::filesystem::path prefix){
    currentPrefix = prefix;
    //spdlog::info("Pefix set to {}", prefix.string());
}

void SetFilePrefixToCurrentDirectory(std::filesystem::path modFolder) {
    currentPrefix = std::filesystem::current_path();
    modDir = modFolder;
    //spdlog::info("Pefix set to {}", currentPrefix.string());
}


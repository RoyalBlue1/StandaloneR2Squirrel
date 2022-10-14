#include <string>
#include <filesystem>
std::filesystem::path currentPrefix;

std::filesystem::path GetFilePrefix() {
    return currentPrefix;
}


void setFilePrefix(std::filesystem::path prefix){
    currentPrefix = prefix;
}

void SetFilePrefixToCurrentDirectory() {
    currentPrefix = std::filesystem::current_path();
}
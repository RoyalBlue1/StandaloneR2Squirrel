#pragma once
#define NOMINMAX // this too
#include <filesystem>


std::filesystem::path GetFilePrefix();
void SetFilePrefix(std::filesystem::path prefix);
void SetFilePrefixToCurrentDirectory();
#include "FileUtils.hpp"
#include <fstream>

std::vector<char> FileUtils::ReadFile(const std::string &filepath)
{
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}
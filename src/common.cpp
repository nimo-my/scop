#include "common.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string &filename)
{
    std::ifstream fin(filename);
    if (!fin.is_open())
    {
        std::cout << "failed to open file: {}" << filename << std::endl;
        return {};
    }
    std::stringstream text;
    text << fin.rdbuf();
    return text.str();
}

//
// Created by lucas on 04/10/2025.
//

#include "../include/CodexManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <base64.h>

CodexManager::CodexManager(ArgParser& o) : _argParser(o)
{
}

void CodexManager::process()
{
    if (_argParser.isDecode()) decode();
    else encode();
}

void CodexManager::encode()
{
    std::string input_str = readData();
    encoded_str = codec::base64::encode(input_str.c_str(), input_str.size());
    writeData(encoded_str.c_str(), encoded_str.size());
}

void CodexManager::decode()
{
    std::string input_str = readData();
    decoded_bytes = codec::base64::decode(input_str.c_str(), input_str.size());
    writeData(reinterpret_cast<char*>(decoded_bytes.data()), decoded_bytes.size());
}

std::string CodexManager::readData() const
{
    std::string input_str;
    if (_argParser.isStringInput())
    {
        input_str = _argParser.getInputFile();
    }
    else
    {
        std::ifstream ifs{_argParser.getInputFile(), std::ios::binary};
        if (!ifs.is_open()) throw std::runtime_error("Input file not found");
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    return input_str;
}

void CodexManager::writeData(const char* bytes, size_t size) const
{
    if (_argParser.isTerminalOutput())
    {
        std::cout.write(bytes, size);
    }
    else
    {
        std::cout
            << " =========== Codex =========== \n"
            << "Mode: " << (_argParser.isDecode() ? "Decode" : "Encode")
            << "Input: " << _argParser.getInputFile()
            << std::endl;

        std::string outputName = _argParser.getOutputFile();
        if (_argParser.isAutoDetect()) outputName += detectExtension(bytes);

        std::ofstream output_file{outputName, std::ios::binary};
        if (!output_file.is_open()) throw std::runtime_error("Could not open output file.");

        std::cout << "Output file: " << outputName << std::endl;
        output_file.write(bytes, size);

        std::cout << " ======== File saved ========= " << std::endl;
    };
}

static std::unordered_set<std::string> well_know_extensions{
    "pdf", "csv", "jpg", "png", "bmp", "tiff ", "ico", "doc", "mp3", "mp4"
};

std::string CodexManager::detectExtension(const char* bytes)
{
    std::string extension = ".";
    for (size_t i = 1; i < 4; i++) extension += std::tolower(bytes[i]);
    if (well_know_extensions.contains(&extension[1])) return extension;
    return ".txt";
}

//
// Created by lucas on 04/10/2025.
//

#include "../include/CodexManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <base64.h>

CodexManager::CodexManager(ArgParser& o): _argParser(o) {}

void CodexManager::process()
{
    if (_argParser.isDecode())  decode();
    else encode();
}

void CodexManager::encode()
{
    std::string input_str = readData();
    encoded_str = codec::base64::encode(input_str.c_str(), input_str.size());
    writeData(encoded_str.c_str());
}

void CodexManager::decode()
{
    std::string input_str = readData();
    decoded_bytes = codec::base64::decode(input_str.c_str(), input_str.size());
    writeData(reinterpret_cast<char*>(decoded_bytes.data()));
}

std::string CodexManager::readData() const
{
    std::string input_str;
    if (_argParser.isStringInput())
    {
        input_str = _argParser.getInputFile();
        std::cout << "Input string: " << input_str << std::endl;
    } else
    {
        std::ifstream ifs{_argParser.getInputFile(), std::ios::binary};
        if (!ifs.is_open()) throw std::runtime_error("Input file not found");

        std::cout << "Input file: " << _argParser.getInputFile() << std::endl;
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    return input_str;
}

void CodexManager::writeData(const char* bytes) const
{
    if (_argParser.isTerminalOutput())
    {
        std::cout << "Output string: " << bytes << std::endl;
    }
    else
    {
        std::ofstream output_file{ _argParser.getOutputFile(), std::ios::binary };
        if (!output_file.is_open()) throw std::runtime_error("Could not open output file.");

        std::cout << "Output file: " << _argParser.getOutputFile() << std::endl;

        output_file << bytes;
    };

    std::cout << " ======== File saved ========= " << std::endl;
}




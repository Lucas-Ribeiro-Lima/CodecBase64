//
// Created by lucas on 04/10/2025.
//

#ifndef CODEXL_CODEXMANAGER_H
#define CODEXL_CODEXMANAGER_H

#include "ArgParser.h"
#include <string>
#include <vector>

class CodexManager
{
    ArgParser& _argParser;
    std::string encoded_str;
    std::vector<unsigned char> decoded_bytes;

    void encode();
    void decode();
    [[nodiscard]] std::string readData() const;
    void writeData(const char* bytes) const;
public:
    explicit CodexManager(ArgParser& o);
    void process();
};


#endif //CODEXL_CODEXMANAGER_H
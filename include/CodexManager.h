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

    void encode(std::string &data);
    void decode(std::string &data);
    [[nodiscard]] std::string readData() const;
    [[nodiscard]] static std::string detectExtension(const char *bytes);

  void writeData(const char *bytes, size_t size) const;
  void process();
  void log(const char *msg, bool isData = false);

public:
  explicit CodexManager(ArgParser &o);
  void execute();
};


#endif //CODEXL_CODEXMANAGER_H

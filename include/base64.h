//
// Created by lucas.lima on 01/10/2025.
//

#ifndef CODEX_BASE64_H
#define CODEX_BASE64_H

#include <string>
#include <vector>

namespace codec::base64
{
    std::string encode(const char* msg, const size_t& size);

    std::vector<unsigned char> decode(const char* encoded, const size_t& size);

    [[deprecated]] std::string bytes_to_string(const std::vector<unsigned char>& bytes);
}


#endif //CODEX_BASE64_H

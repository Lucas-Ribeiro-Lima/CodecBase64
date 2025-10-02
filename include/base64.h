//
// Created by lucas.lima on 01/10/2025.
//

#ifndef CODECBASE64_BASE64_H
#define CODECBASE64_BASE64_H

#include <string>
#include <vector>

namespace codec::base64
{
    void _encode_block(const unsigned char* buffer, std::string& encoded);

    void _decode_block(const unsigned char* buffer, std::vector<unsigned char>& decoded);

    std::string encode(const char* msg, const size_t& size);

    std::vector<unsigned char> decode(const char* encoded, const size_t& size);

    std::string bytes_to_string(const std::vector<unsigned char>& bytes);
}


#endif //CODECBASE64_BASE64_H

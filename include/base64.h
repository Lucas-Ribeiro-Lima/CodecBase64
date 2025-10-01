//
// Created by lucas.lima on 01/10/2025.
//

#include <string>
#include <vector>

#ifndef CODECBASE64_BASE64_H
#define CODECBASE64_BASE64_H

namespace crypt {
  namespace base64 {
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    void _encode_block(const unsigned char *buffer, std::string &encoded);

    void _decode_block(const unsigned char *buffer, std::vector<unsigned char> &decoded);

    std::string encode(const unsigned char *msg);

    std::vector<unsigned char> decode(const std::string &encoded);

    std::string bytes_to_string(const std::vector<unsigned char> &bytes);
  }
}

#endif //CODECBASE64_BASE64_H

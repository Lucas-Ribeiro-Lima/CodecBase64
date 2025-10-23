//
// Created by lucas.lima on 23/10/2025.
//

#ifndef CODEXL_HEX_H
#define CODEXL_HEX_H

#include <string>
#include <vector>

namespace codec::hex {
  std::string encode(const char* msg, const size_t& size);

  std::vector<unsigned char> decode(const char* encoded, const size_t& size);
}


#endif //CODEXL_HEX_H

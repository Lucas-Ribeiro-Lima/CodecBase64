//
// Created by lucas.lima on 23/10/2025.
//

#include <hex.h>
#include <array>
#include <stdexcept>

#define FIRST_NIBBLE_BITS 0xF0
#define SECOND_NIBBLE_BITS 0x0F


namespace codec::hex {
  static const std::string hex_chars = "0123456789ABCDEF";

  static constexpr std::array<char, 256> hex_lut = [] {
    std::array<char, 256> tmp;

    tmp.fill(0);

    for (char c = '0'; (c <= '9'); c++) {
      tmp[c] = c - '0';
    }

    for (char c = 'A'; c <= 'F'; c++) {
      tmp[c] = c - 'A' + 10;
    }

    return tmp;
  }();

  std::string encode(const char *msg, const size_t &size) {
    std::string buffer;

    for (size_t it = 0; it < size; ++it) {
      const char c = msg[it];

      unsigned char first_nibble = (c & FIRST_NIBBLE_BITS) >> 4;
      unsigned char second_nibble = c & SECOND_NIBBLE_BITS;

      buffer += hex_chars[first_nibble];
      buffer += hex_chars[second_nibble];
    }

    return buffer;
  }

  std::vector<unsigned char> decode(const char *encoded, const size_t &size) {
    std::vector<unsigned char> buffer;

    if (size & 1) throw std::invalid_argument("Invalid size");

    for (size_t it = 1; it < size; it += 2) {
      char tmp[2] = {encoded[it - 1], encoded[it]};

      char byte = hex_lut[tmp[0]] << 4 | hex_lut[tmp[1]] & SECOND_NIBBLE_BITS;
      buffer.push_back(byte);
    }

    return buffer;
  }
}

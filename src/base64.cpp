//
// Created by lucas.lima on 01/10/2025.
//

#include <base64.h>

namespace crypt {
  namespace base64 {
    void _encode_block(const unsigned char *buffer, std::string &encoded) {
      std::string tmp_buffer;
      char out_buffer[4] = {0, 0, 0, 0};

      out_buffer[0] = (buffer[0] >> 2) & 0x3F;
      out_buffer[1] = ((buffer[0] & 0x03) << 4) | (buffer[1] >> 4) & 0x3F;
      out_buffer[2] = ((buffer[1] & 0x0F) << 2) | (buffer[2] >> 6) & 0x3F;
      out_buffer[3] = buffer[2] & 0x3F;

      for (size_t i = 0; i < 4; i++) tmp_buffer += base64_chars[out_buffer[i]];

      encoded += tmp_buffer;
    }

    void _decode_block(const unsigned char *buffer, std::vector<unsigned char> &decoded) {
      unsigned char out_buffer[3] = {0, 0, 0};
      out_buffer[0] = buffer[0] << 2 | buffer[1] >> 4;
      out_buffer[1] = (buffer[1] & 0x0F) << 4 | buffer[2] >> 2;
      out_buffer[2] = (buffer[2] & 0x03) << 6 | buffer[3] & 0x3F;

      for (char i: out_buffer) decoded.push_back(i);

    }

    std::string encode(const unsigned char *msg) {
      std::string encoded;
      unsigned char buffer[3] = {0, 0, 0};

      size_t counter = 0;
      for (size_t it = 0; msg[it] != '\0'; it++) {
        if (counter < 3) {
          buffer[counter++] = msg[it];
          continue;
        }

        _encode_block(buffer, encoded);
        buffer[0] = msg[it];
        counter = 1;
      }

      size_t padding = 3 - counter;
      for (; counter < 3; counter++) buffer[counter] = 0;


      _encode_block(buffer, encoded);
      encoded.replace(encoded.size() - padding, padding, "=");

      return encoded;
    }

    std::vector<unsigned char> decode(const std::string &encoded) {
      unsigned char buffer[4] = {0, 0, 0, 0};
      std::vector<unsigned char> decoded;

      size_t counter = 0;
      for (auto &c: encoded) {
        if (counter < 4) {
          int pos = base64_chars.find(c);
          if (pos == -1) break;
          buffer[counter++] = pos;
          continue;
        }
        _decode_block(buffer, decoded);

        buffer[0] = base64_chars.find(c);
        counter = 1;
      }

      for (; counter < 4; counter++) buffer[counter] = 0;


      _decode_block(buffer, decoded);

      return decoded;
    }

    std::string bytes_to_string(const std::vector<unsigned char> &bytes) {
      std::string res;
      for (auto &c: bytes) res += c;
      return res;
    }
  }
}

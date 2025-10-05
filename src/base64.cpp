//
// Created by lucas.lima on 01/10/2025.
//

#include <base64.h>
#include <array>

#define BASE64_CHAR_COUNT 4
#define BASE64_BYTE_COUNT 3
#define BASE64_PADDING_CHAR "="

#define STRING_NULL_TERMINATOR '\0'

#define SIX_LSB_BITS 0x3F
#define FOUR_LSB_BITS 0x0F
#define TWO_LSB_BITS 0x03

namespace codec::base64
{
    static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    static constexpr std::array<char, 256> base64_lut = [] {
      std::array<char, 256> lut{};
      lut.fill(-1);

      for (int i = 'A'; i <= 'Z'; ++i) lut[i] = i - 'A';           // 0–25
      for (int i = 'a'; i <= 'z'; ++i) lut[i] = i - 'a' + 26;      // 26–51
      for (int i = '0'; i <= '9'; ++i) lut[i] = i - '0' + 52;      // 52–61
      lut['+'] = 62;
      lut['/'] = 63;

      return lut;
    }();

    void _encode_block(const unsigned char* buffer, std::string& encoded)
    {
        std::string tmp_buffer;
        char out_buffer[BASE64_CHAR_COUNT] = {0, 0, 0, 0};

        out_buffer[0] = (buffer[0] >> 2) & SIX_LSB_BITS;
        out_buffer[1] = ((buffer[0] & TWO_LSB_BITS) << 4) | (buffer[1] >> 4) & SIX_LSB_BITS;
        out_buffer[2] = ((buffer[1] & FOUR_LSB_BITS) << 2) | (buffer[2] >> 6) & SIX_LSB_BITS;
        out_buffer[3] = buffer[2] & SIX_LSB_BITS;

        for (size_t i = 0; i < BASE64_CHAR_COUNT; i++) tmp_buffer += base64_chars[out_buffer[i]];

        encoded += tmp_buffer;
    }

    void _decode_block(const unsigned char* buffer, std::vector<unsigned char>& decoded)
    {
        unsigned char out_buffer[BASE64_BYTE_COUNT] = {0, 0, 0};
        out_buffer[0] = buffer[0] << 2 | buffer[1] >> 4;
        out_buffer[1] = (buffer[1] & FOUR_LSB_BITS) << 4 | buffer[2] >> 2;
        out_buffer[2] = (buffer[2] & TWO_LSB_BITS) << 6 | buffer[3] & SIX_LSB_BITS;

        for (char i : out_buffer) decoded.push_back(i);
    }

    std::string encode(const char* msg, const size_t& size)
    {
        std::string encoded;
        unsigned char buffer[BASE64_BYTE_COUNT] = {0, 0, 0};

        size_t counter = 0;
        for (size_t it = 0; it < size; it++)
        {
            if (counter < 3)
            {
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
        encoded.replace(encoded.size() - padding, padding, BASE64_PADDING_CHAR);

        return encoded;
    }

    std::vector<unsigned char> decode(const char* encoded, const size_t& size)
    {
        unsigned char buffer[BASE64_CHAR_COUNT] = {0, 0, 0, 0};
        std::vector<unsigned char> decoded;

        size_t counter = 0;
        size_t padding = 0;

        for (size_t it = 0; it < size;)
        {
            if (counter < BASE64_CHAR_COUNT)
            {
                char pos = base64_lut[encoded[it]];
                if (pos != std::string::npos) buffer[counter++] = pos;
                else
                {
                    buffer[counter++] = 0;
                    padding++;
                }
                it++;
                continue;
            }
            _decode_block(buffer, decoded);
            counter = 0;
        }

        _decode_block(buffer, decoded); //Compute the last block

        decoded.erase(decoded.end() - padding, decoded.end());

        return decoded;
    }

    [[deprecated]] std::string bytes_to_string(const std::vector<unsigned char>& bytes)
    {
        std::string res;
        for (auto& c : bytes) res += c;
        return res;
    }
}

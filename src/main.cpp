#include <base64.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define USAGE_MESSAGE \
            "Usage: [mode] [input file] [output file]" "\n" \
            "e.g. CodecBase64 --decode input_file.txt output_file.jpg" "\n\n" \
            "Modes: " "\n" \
            "    --code, -c    Codify the bytes with base64 encoding" "\n" \
            "    --decode, -d  Decodify a base64 text file to bytes"  "\n" \
            "Input: Path to the file with the string" "\n" \
            "Output: Path where the output file will be created" "\n"

#define ARGV_OPTIONS_COUNT 4
#define ARGV_INPUT_FILE 2
#define ARGV_OUTPUT_FILE 3

int main(int argc, char* argv[])
{
    if (argc != ARGV_OPTIONS_COUNT)
    {
        std::cout << USAGE_MESSAGE << std::endl;
        return 1;
    }

    try
    {
        std::ifstream infile{argv[ARGV_INPUT_FILE], std::ios::binary};
        std::ofstream outfile{argv[ARGV_OUTPUT_FILE], std::ios::binary};

        if (!infile.is_open() || !outfile.is_open())
        {
            throw std::runtime_error("Failed to open input/output file");
        }

        std::ostringstream oss;
        oss << infile.rdbuf();
        std::string input_str = oss.str();

        std::vector<unsigned char> decoded_bytes = crypt::base64::decode(input_str.c_str());
        outfile.write(reinterpret_cast<char*>(decoded_bytes.data()), decoded_bytes.size());
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

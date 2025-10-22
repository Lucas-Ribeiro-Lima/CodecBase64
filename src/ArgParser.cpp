//
// Created by lucas.lima on 03/10/2025.
//

#include "../include/ArgParser.h"
#include <iostream>
#include <unordered_map>

#define USAGE_MESSAGE \
"Usage: [mode] [options] [encoder/decoder] [input file] [output file]" "\n" \
"e.g. codex --decode base64 input_file.txt output_file.jpg" "\n" \
"Modes: " "\n" \
"    -e/--encode   Codify the bytes with the specified encoding algorithm" "\n" \
"    -d/--decode Decodify the file with the specified encoding algorithm."  "\n" \
"                    Not every encoder permits a decoding, like the hash function sha256!" "\n" \
"Input: "  "\n" \
"    -r  Recursive mode. " "\n" \
"                On encode the output file will concatenate the data with \\n." "\n" \
"                On decode recursive mode output files will be incremented named." "\n" \
"                Type auto-detected obrigatory on recursive." "\n" \
"    -s  String input mode. The string passed as input will be parsed as the data." "\n"\
"Output: " "\n" \
"    -t  Terminal output mode. The content will be redirect to stdout." "\n" \
"    -x  File type auto-detect mode" "\n" \
"                If none magic signature found, the fallback type is .txt." "\n" \
"Input: Path to the file with the string" "\n" \
"Output: Path where the output file will be created" "\n" \
"TO DO" "\n" \
"Encoders: " "\n" \
"     * base64" "\n" \
"     * hex" "\n" \
"     * sha256" "\n" \

#define ARGV_MIN_COUNT 5
#define ARGV_MODE_OPTION 1

#define STRING_INPUT_MASK 0x01
#define TERMINAL_OUTPUT_MASK 0x02
#define RECURSIVE_MASK 0x04
#define AUTO_DETECT_MASK 0x08

#define DECODE_MODE_MASK 0x10
#define ENCODE_MODE_MASK  0x20

#define ERRORS_MASK 0x80

enum options_enum
{
    ENCODE = 'e',
    DECODE = 'd',
    STRING_INPUT = 's',
    TERMINAL_OUTPUT = 't',
    AUTO_DETECT = 'x',
    RECURSIVE = 'r',
};

static std::unordered_map<char, unsigned char> options_map{
    {ENCODE, ENCODE_MODE_MASK},
    {DECODE, DECODE_MODE_MASK},
    {STRING_INPUT, STRING_INPUT_MASK},
    {TERMINAL_OUTPUT, TERMINAL_OUTPUT_MASK},
    {AUTO_DETECT, AUTO_DETECT_MASK},
    {RECURSIVE, RECURSIVE_MASK}
};

ArgParser::ArgParser(int argc, char* argv[])
{
    if (argc < ARGV_MIN_COUNT)
    {
        std::cout
            << "Invalid numbers of arguments: " << argc << "\n"
            << USAGE_MESSAGE << std::endl;
        options |= ERRORS_MASK;
        return;
    }

    input_file = argv[argc - 2];
    output_file = argv[argc - 1];

    std::string encoding_algorithm = argv[argc - 3];
    if (encoding_algorithm == "base64") encoder = Encoders::Base64;
    else if (encoding_algorithm == "hex") encoder = Encoders::HEX;
    else if (encoding_algorithm == "sha256") encoder = Encoders::SHA256;

    for (size_t it = 1; it < argc - 3; it++)
    {
        std::string _arg = argv[it];
        for (auto& c : _arg)
        {
            if (c == '-') continue;
            if (options_map.contains(c))
            {
                options |= options_map[c];
            }
            else
            {
                std::cout << "Invalid options: " << c << ", ";
                options |= ERRORS_MASK;
            }
        }
    }

    if (options & DECODE_MODE_MASK && options & ENCODE_MODE_MASK)
    {
        std::cout << "Encode and decoded options simultaneously selected." << std::endl;
        options |= ERRORS_MASK;
    }

    if (hasError())
    {
        std::cout << USAGE_MESSAGE << std::endl;
        return;
    }
}

const char* ArgParser::getInputFile() const
{
    return input_file;
}

const char* ArgParser::getOutputFile() const
{
    return output_file;
}

Encoders ArgParser::getEncoder() const
{
    return encoder;
}


bool ArgParser::isDecode() const
{
    return options & DECODE_MODE_MASK;
}

bool ArgParser::isAutoDetect() const
{
    return options & AUTO_DETECT_MASK;
}

bool ArgParser::isRecursive() const
{
    return options & RECURSIVE_MASK;
}

bool ArgParser::isStringInput() const
{
    return options & STRING_INPUT_MASK;
}

bool ArgParser::isTerminalOutput() const
{
    return options & TERMINAL_OUTPUT_MASK;
}

bool ArgParser::hasError() const
{
    return options & ERRORS_MASK;
}

void ArgParser::setInputFile(const char *file) {
  input_file = file;
}

void ArgParser::setOutputFile(const char *file) {
  output_file = file;
}

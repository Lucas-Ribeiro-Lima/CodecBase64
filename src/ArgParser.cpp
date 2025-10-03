//
// Created by lucas.lima on 03/10/2025.
//

#include "../include/ArgParser.h"
#include <iostream>

#define USAGE_MESSAGE \
"Usage: [mode] [options] [encoder/decoder] [input file] [output file]" "\n" \
"e.g. codex --decode base64 input_file.txt output_file.jpg" "\n" \
"Modes: " "\n" \
"    -c/--encode   Codify the bytes with the specified encoding algorithm" "\n" \
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
"    -e  File type auto-detect mode" "\n" \
"                If none magic signature found, the fallback type is .bin." "\n" \
"Encoders:" "\n" \
"     * base64" "\n" \
"     * hex" "\n" \
"     * sha256" "\n" \
"Input: Path to the file with the string" "\n" \
"Output: Path where the output file will be created" "\n"

#define ARGV_MIN_COUNT 5
#define ARGV_MODE_OPTION 1

#define STRING_INPUT_MASK 0x01
#define TERMINAL_OUTPUT_MASK 0x02
#define RECURSIVE_MASK 0x04
#define AUTO_DETECT_MASK 0x08

#define DECODE_MODE_MASK 0x10
#define ENCODE_MODE_MASK  0x20

#define ERRORS_MASK 0x80

ArgParser::ArgParser(int argc, char *argv[]):
 input_file(argv[argc - 2]), output_file(argv[argc - 1])
{
  if (argc < ARGV_MIN_COUNT) {
    std::cout
      << "Invalid numbers of arguments: " << argc << "\n"
      << USAGE_MESSAGE << std::endl;
    options |= ERRORS_MASK;
    return;
  }

  char *mode_str = argv[ARGV_MODE_OPTION];
  if (mode_str[0] == '-' && mode_str[1] == 'c') options |= ENCODE_MODE_MASK;
  else if (mode_str[0] == '-' && mode_str[1] == 'd') options |= DECODE_MODE_MASK;

  if (mode_str[0] == '-' && mode_str[1] == '-') {
    if (strcmp(&mode_str[2], "decode") == 0) {
      options |= DECODE_MODE_MASK;
    }
    if (strcmp(&mode_str[2], "encode") == 0) {
      options |= ENCODE_MODE_MASK;
    }
  }

  if (!(options & DECODE_MODE_MASK ^ options & ENCODE_MODE_MASK)) {
    std::cout << "Invalid mode: " << mode_str << std::endl;
    std::cout << USAGE_MESSAGE << std::endl;
    options |= ERRORS_MASK;
    return;
  }
}

const char *ArgParser::getInputFile() const {
  return input_file;
}

const char *ArgParser::getOutputFile() const {
  return output_file;
}

bool ArgParser::isDecode() const {
  if (options & ENCODE_MODE_MASK && options & DECODE_MODE_MASK) throw std::invalid_argument("Duplicate mode");
  return options & DECODE_MODE_MASK;
}

bool ArgParser::isAutoDetect() const {
  return options & AUTO_DETECT_MASK;
}

bool ArgParser::isRecursive() const {
  return options & RECURSIVE_MASK;
}

bool ArgParser::isStringInput() const {
  return options & STRING_INPUT_MASK;
}

bool ArgParser::isTerminalOutput() const {
  return options & TERMINAL_OUTPUT_MASK;
}

bool ArgParser::hasError() {
  return options & ERRORS_MASK;
}


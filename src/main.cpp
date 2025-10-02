#include <base64.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#define USAGE_MESSAGE \
            "Usage: [mode] [options] [encoder/decoder] [input file] [output file]" "\n" \
            "e.g. codex --decode base64 input_file.txt output_file.jpg" "\n" \
            "Modes: " "\n" \
            "    -c/--code   Codify the bytes with the specified encoding algorithm" "\n" \
            "    -d/--decode Decodify the file with the specified encoding algorithm."  "\n" \
            "                    Not every encoder permits a decoding, like the hash function sha256!" "\n" \
            "Input: "  "\n" \
            "    -f  File input mode (Default)."  "\n" \
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

#define ARGV_OPTIONS_COUNT 4
#define ARGV_MODE_OPTION 1
#define ARGV_INPUT_FILE 2
#define ARGV_OUTPUT_FILE 3

const char *DECODE_MODE = "decode";
const char *CODE_MODE = "code";

int main(int argc, char *argv[]) {
  if (argc != ARGV_OPTIONS_COUNT) {
    std::cout << USAGE_MESSAGE << std::endl;
    return 1;
  }

  int decode = -1;
  char *mode = argv[ARGV_MODE_OPTION];
  if (mode[0] == '-' && mode[1] == 'c') decode = 0;
  else if (mode[0] == '-' && mode[1] == 'd') decode = 1;

  if (mode[0] == '-' && mode[1] == '-') {
    if (strcmp(&mode[2], DECODE_MODE) == 0) {
      decode = 1;
    }
    if (strcmp(&mode[2], CODE_MODE) == 0) {
      decode = 0;
    }
  }

  if (decode == -1) {
    std::cout << "Invalid mode: " << mode << std::endl;
    std::cout << USAGE_MESSAGE << std::endl;
    return 1;
  }

  std::cout
      << " =========== Codex =========== \n"
      << "Mode: " << ((mode[1] == '-') ? &mode[2] : &mode[1])
      << "\n" "Input file: " << argv[ARGV_INPUT_FILE]
      << "\n" "Saving file at: " << argv[ARGV_OUTPUT_FILE]
      << std::endl;

  try {
    std::ifstream infile{argv[ARGV_INPUT_FILE], std::ios::binary};
    std::ofstream outfile{argv[ARGV_OUTPUT_FILE], std::ios::binary};

    if (!infile.is_open() || !outfile.is_open()) {
      throw std::runtime_error("Failed to open input/output file");
    }

    std::ostringstream oss;
    oss << infile.rdbuf();
    std::string input_str = oss.str();

    if (decode) {
      std::vector<unsigned char> decoded_bytes = codec::base64::decode(input_str.c_str(), input_str.length());
      outfile.write(reinterpret_cast<char *>(decoded_bytes.data()), decoded_bytes.size());
    } else {
      std::string encoded_str =
          codec::base64::encode(input_str.c_str(), input_str.length());
      outfile.write(encoded_str.data(), encoded_str.size());
    }

    std::cout << " ======== File saved ========= " << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }

  return 0;
}

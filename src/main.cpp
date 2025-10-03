#include <base64.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ArgParser.h"


int main(int argc, char *argv[]) {
  ArgParser options{argc, argv};

  if (options.hasError()) return -1;

  std::cout
      << " =========== Codex =========== \n"
      << "Mode: " << (options.isDecode() ? "Decode" : "Encode")
      << "\n" "Input file: " << options.getInputFile()
      << "\n" "Saving file at: " << options.getOutputFile()
      << std::endl;

  try {
    std::ifstream infile{options.getInputFile(), std::ios::binary};
    std::ofstream outfile{options.getOutputFile(), std::ios::binary};

    if (!infile.is_open() || !outfile.is_open()) {
      throw std::runtime_error("Failed to open input/output file");
    }

    std::ostringstream oss;
    oss << infile.rdbuf();
    std::string input_str = oss.str();

    if (options.isDecode()) {
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

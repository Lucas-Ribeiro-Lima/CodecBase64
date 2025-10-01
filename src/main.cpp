#include <base64.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cout \
    << "Usage: [mode] [input file] [output file]" << "\n" \
    << "Mode's support: [-c --code, -d --decode]" << "\n" \
    << "Input formats support: [.txt]" << std::endl;
  }

  try {
    std::ifstream infile{ argv[2], std::ios::binary };
    std::ofstream outfile{ argv[3], std::ios::binary };

    if (!infile.is_open() || !outfile.is_open()) {
      throw std::runtime_error("Failed to open input/output file");
    }

    std::ostringstream oss;
    oss << infile.rdbuf();
    std::string input_str = oss.str();

    std::vector<unsigned char> decoded_bytes = crypt::base64::decode(input_str);
    outfile.write(reinterpret_cast<char*>(decoded_bytes.data()), decoded_bytes.size());

  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
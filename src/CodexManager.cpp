//
// Created by lucas on 04/10/2025.
//

#include "../include/CodexManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <base64.h>

CodexManager::CodexManager(ArgParser &o) : _argParser(o) {
}

void CodexManager::execute() {
  if (!_argParser.isTerminalOutput()) {
    std::cout
        << " =========== Codex =========== \n"
        << "Mode: " << (_argParser.isDecode() ? "Decode" : "Encode")
        << std::endl;
  }

  if (_argParser.isRecursive()) {
    if (!std::filesystem::is_directory(_argParser.getInputFile()))
      throw std::invalid_argument("Input file is not a directory");

    std::filesystem::recursive_directory_iterator dir(_argParser.getInputFile());

    size_t counter = 1;
    for (auto &entry: dir) {
      if (std::filesystem::is_regular_file(entry)) {
        std::filesystem::path p = entry.path();

        std::string inputFile = p.string();
        std::string outputFile = p.filename().replace_extension("").string() + "_" + std::to_string(counter++);

        _argParser.setInputFile(inputFile.c_str());
        _argParser.setOutputFile(outputFile.c_str());

        if (!_argParser.isTerminalOutput()) {
          std::cout << "Processing: " << inputFile << "\n";
          std::cout << "Output file: " << outputFile << std::endl;
        }

        process();

      }
    }
    if (!_argParser.isTerminalOutput()) std::cout << " ======== Files saved ========= \n" << std::endl;
  } else {
    std::cout << "Processing: " << _argParser.getInputFile();
    process();
  }
}

void CodexManager::process() {
  std::string data = readData();
  if (_argParser.isDecode()) decode(data);
  else encode(data);
}


void CodexManager::encode(std::string &data) {
  encoded_str = codec::base64::encode(data.c_str(), data.size());
  writeData(encoded_str.c_str(), encoded_str.size());
}

void CodexManager::decode(std::string &data) {
  decoded_bytes = codec::base64::decode(data.c_str(), data.size());
  writeData(reinterpret_cast<char *>(decoded_bytes.data()), decoded_bytes.size());
}

std::string CodexManager::readData() const {
  std::string input_str;
  if (_argParser.isStringInput()) {
    input_str = _argParser.getInputFile();
  } else {
    std::ifstream ifs{_argParser.getInputFile(), std::ios::binary};
    if (!ifs.is_open()) throw std::runtime_error("Input file not found");
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
  }

  return input_str;
}

void CodexManager::writeData(const char *bytes, size_t size) const {
  if (_argParser.isTerminalOutput()) {
    std::cout.write(bytes, size) << "\n";
  } else {
    std::string outputName = _argParser.getOutputFile();
    if (_argParser.isAutoDetect()) outputName += detectExtension(bytes);

    std::ofstream output_file{outputName, std::ios::binary};
    if (!output_file.is_open()) throw std::runtime_error("Could not open output file.");

    output_file.write(bytes, size);
  };
}

void CodexManager::log(const char *msg, bool isData) {
  if (_argParser.isTerminalOutput() && !isData) return;
  std::cout << msg;
}


static std::unordered_set<std::string> well_know_extensions{
  "pdf", "csv", "jpg", "png", "bmp", "tiff ", "ico", "doc", "mp3", "mp4"
};

std::string CodexManager::detectExtension(const char *bytes) {
  std::string extension = ".";
  for (size_t i = 1; i < 4; i++) extension += std::tolower(bytes[i]);
  if (well_know_extensions.contains(&extension[1])) return extension;
  return ".txt";
}

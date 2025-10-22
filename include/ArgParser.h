//
// Created by lucas.lima on 03/10/2025.
//

#ifndef CODEX_ARGPARSER_H
#define CODEX_ARGPARSER_H

enum  Encoders {
  Base64,
  HEX,
  SHA256
};

class ArgParser {
  const char* input_file = nullptr;
  const char* output_file = nullptr;
  unsigned char options = 0;
  Encoders encoder;

public:
  ArgParser(int argc, char *argv[]);
  [[nodiscard]] bool isRecursive() const;
  [[nodiscard]] bool isStringInput() const;
  [[nodiscard]] bool isTerminalOutput() const;
  [[nodiscard]] bool isDecode() const;
  [[nodiscard]] bool isAutoDetect() const;
  [[nodiscard]] Encoders getEncoder() const;
  void setInputFile(const char * file);
  void setOutputFile(const char * file);
  const char* getInputFile() const;
  const char* getOutputFile() const;
  bool hasError() const;
};


#endif //CODEX_ARGPARSER_H

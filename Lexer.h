// Lexer.h
//

#pragma once

#define SOURCE_FILE_IO_MODE "r"

#include "SymbolTable.h"
#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>

struct Lexer {
private:
  FILE *_fd;
  std::string _sourceFile;
  unsigned int _lineNumber;
  SymbolTable &_SymbolTable;
  std::array<char, 1024> _line;
  std::string _classifyToken(std::string token);

  std::unordered_set<std::string> _opToken = {
      "=", "<", ">", "==", "<=", ">=", "!=", "+",
      "-", "*", "/", "%",  ":",  "^",  "~",  "!"};

  std::unordered_set<std::string> _syntaxToken = {
      "\"", "'", "(", ")", "{", "}", "[", "]"};

  std::vector<std::pair<std::unordered_set<std::string>,
                        std::string>>
      _types = {{_opToken, KIND_OPERATOR},
                {_syntaxToken, KIND_SYNTAX}};

public:
  Lexer(std::string sourceFile, SymbolTable &symbolTable);
  std::string getFileExtension(void);
  unsigned int getLineNumber(void);
  bool openFile(void);
  bool readLine(void);
  void setLine(std::string line);
  std::vector<std::pair<std::string, std::string>>
  tokenize(void);
  ~Lexer() {
    if (_fd) {
      fclose(_fd);
    }
  }
};

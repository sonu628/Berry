// Lexer.h
//

#pragma once

#define SOURCE_FILE_IO_MODE "r"
#define HISTORY_FILE_IO_MODE "w"
#define HISTORY_FILE "BerryHistory"

#include "SymbolTable.h"
#include <array>
#include <iostream>
#include <unordered_set>
#include <vector>

struct Lexer {
private:
  FILE *_fd, *_hisFd;
  std::string _sourceFile;
  unsigned int _lineNumber;
  SymbolTable &_SymbolTable;
  std::array<char, 1024> _line{};
  TokenType _classifyToken(const std::string &token);

  std::unordered_set<std::string> _opToken = {
      "=", "<", ">", "==", "<=", ">=", "!=", "+",
      "-", "*", "/", "%",  ":",  "^",  "~",  "!"};

  std::unordered_set<std::string> _syntaxToken = {
      "\"", "'", "(", ")", "{", "}", "[", "]"};

  std::vector<std::pair<std::unordered_set<std::string>,
                        enum TokenType>>
      _types = {{_opToken, TokenType::Operator},
                {_syntaxToken, TokenType::Syntax}};

public:
  Lexer(std::string sourceFile, SymbolTable &SymbolTable_);
  std::string getFileExtension(void);
  unsigned int getLineNumber(void);
  bool openFile(void);
  bool readLine(void);
  void setLine(const std::string &line);
  std::vector<std::pair<std::string, TokenType>>
  tokenize(void);
  ~Lexer() {
    if (_fd) {
      fclose(_fd);
    }

    if (_hisFd) {
      fclose(_hisFd);
    }
  }
};

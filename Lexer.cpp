// Lexer.cpp
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Lexer.h"
#include "Error.h"
#include "Token.h"
#include <regex>
#include <unordered_set>

Lexer::Lexer(std::string sourceFile,
             SymbolTable &symbolTable)
    : _fd(NULL), _sourceFile(sourceFile), _lineNumber(0),
      _SymbolTable(symbolTable) {}

unsigned int Lexer::getLineNumber(void) {
  return _lineNumber;
}

std::string Lexer::getFileExtension(void) {
  if (static_cast<int>(_sourceFile.size()) == 0) {
    return "";
  }

  std::size_t pos = _sourceFile.find_last_of(".");
  if (pos == std::string::npos) {
    return "";
  }

  return _sourceFile.substr(pos + 1);
}

bool Lexer::openFile(void) {
  _fd = fopen(_sourceFile.c_str(), SOURCE_FILE_IO_MODE);
  return _fd != NULL;
}

std::string Lexer::_classifyToken(std::string token) {
  std::string type = KIND_UK;
  for (std::pair<std::unordered_set<std::string>,
                 std::string>
           p : _types) {
    if (p.first.find(token) != std::end(p.first)) {
      type = p.second;
    }
  }

  return type;
}

bool Lexer::readLine(void) {
  _lineNumber++;
  return fgets(_line.data(), static_cast<int>(_line.size()),
               _fd) != NULL;
}

void Lexer::setLine(std::string line) {
  _lineNumber++;
  strcpy(_line.data(), line.c_str());
}

std::vector<std::pair<std::string, std::string>>
Lexer::tokenize(void) {
  std::string s = _line.data();
  std::regex rg("[$\\w']+|[?#!<>=()+-/*\"]");
  std::vector<std::pair<std::string, std::string>> tokens;
  std::sregex_token_iterator itr(std::begin(s), std::end(s),
                                 rg);
  std::sregex_token_iterator end;

  int nquote = 0;
  for (; itr != end; itr++) {
    std::string tk = *itr;
    /**
     * We shouldn't be processing/receiving anymore tokens
     * after we've seen the last (closing) double quote.
     */
    if (nquote == 2) {
      throw std::invalid_argument(Error::Format(
          Error::tokenAfterQuote, tk.c_str()));
    }

    if (Token::getKind(tk) == Token::Kind::HashTag) {
      return tokens;
    }

    if (Token::getKind(tk) == Token::Kind::DoubleQuote) {
      nquote++;
    }

    tokens.push_back({tk, _classifyToken(tk)});
  }

  return tokens;
}

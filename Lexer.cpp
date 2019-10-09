// Lexer.cpp
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Lexer.h"
#include "Error.h"
#include "Token.h"
#include <cstdio>
#include <regex>
#include <unordered_set>
#include <utility>

Lexer::Lexer(std::string sourceFile,
             SymbolTable &SymbolTable_)
    : _fd(nullptr),
      _hisFd(fopen(HISTORY_FILE, HISTORY_FILE_IO_MODE)),
      _sourceFile(std::move(sourceFile)), _lineNumber(0),
      _SymbolTable(SymbolTable_), _line{} {}

unsigned int Lexer::getLineNumber(void) {
  return _lineNumber;
}

std::string Lexer::getFileExtension(void) {
  if (_sourceFile.empty()) {
    return "";
  }

  std::size_t pos = _sourceFile.find_last_of('.');
  if (pos == std::string::npos) {
    return "";
  }

  return _sourceFile.substr(pos + 1);
}

bool Lexer::openFile(void) {
  _fd = fopen(_sourceFile.c_str(), SOURCE_FILE_IO_MODE);
  return _fd != nullptr;
}

TokenType Lexer::_classifyToken(const std::string &token) {
  TokenType type = TokenType::UnRec;
  for (std::pair<std::unordered_set<std::string>, TokenType>
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
               _fd) != nullptr;
}

void Lexer::setLine(const std::string &line) {
  _lineNumber++;
  strcpy(_line.data(), line.c_str());
}

std::vector<std::pair<std::string, TokenType>>
Lexer::tokenize(void) {
  if (!_hisFd) {
    throw std::invalid_argument(
        Error::Format(Error::fileWrite));
  }

  std::array<char, 1024> buf{};
  sprintf(buf.data(), "%s\n", _line.data());
  fputs(buf.data(), _hisFd);

  std::string s = _line.data();
  std::regex rg("[$\\w']+|[?#!<>=()+-/*\"]");
  std::vector<std::pair<std::string, TokenType>> tokens;
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

    switch (Token::getKind(tk)) {
    case Token::Kind::HashTag:
      return tokens;
    case Token::Kind::DoubleQuote:
      nquote++;
      break;
    /* To silence the compiler */
    default:;
    }

    tokens.push_back({tk, _classifyToken(tk)});
  }

  if (nquote != 0 && nquote != 2) {
    throw std::invalid_argument(
        Error::Format(Error::noClosingQuote));
  }

  return tokens;
}

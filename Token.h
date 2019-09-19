// Token.h
//

#pragma once

#include <iostream>

namespace Token {
enum Kind {
  // Operators
  EqualTo,
  LessThan,
  GreaterThan,
  Comparison,
  LessThanEqual,
  GreaterThanEqual,
  NotEqualTo,

  // Syntax
  Dollar,
  SingleQuote,
  DoubleQuote,
  ForwardSlash,
  BeginComment,
  HashTag,

  // Built-in
  Declr,
  Else,
  Endif,
  If,
  Println,
  Readln,

  // default
  Unknown
};

enum Kind getKind(char c);
enum Kind getKind(const std::string& s);
bool isValidLiteral(std::string s);
bool isValidToken(std::string s);
void trimQuotes(std::string &s);
} // namespace Token
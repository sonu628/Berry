// Token.cpp
//

#include "Token.h"
#include "Error.h"
#include <algorithm>
#include <cassert>

enum Token::Kind Token::getKind(char c) {
  return getKind(std::string(1, c));
}

enum Token::Kind Token::getKind(std::string s) {
  if (s == "=")
    return Token::Kind::EqualTo;
  if (s == "<")
    return Token::Kind::LessThan;
  if (s == ">")
    return Token::Kind::GreaterThan;
  if (s == "==")
    return Token::Kind::Comparison;
  if (s == "<=")
    return Token::Kind::LessThanEqual;
  if (s == ">=")
    return Token::Kind::GreaterThanEqual;
  if (s == "!=")
    return Token::Kind::NotEqualTo;
  if (s == "$")
    return Token::Kind::Dollar;
  if (s == "'")
    return Token::Kind::SingleQuote;
  if (s == "\"")
    return Token::Kind::DoubleQuote;
  if (s == "/")
    return Token::Kind::ForwardSlash;
  if (s == "//")
    return Token::Kind::BeginComment;
  if (s == "#")
    return Token::Kind::HashTag;
  if (s == "let" || s == "var")
    return Token::Kind::Declr;
  if (s == "else")
    return Token::Kind::Else;
  if (s == "endif")
    return Token::Kind::Endif;
  if (s == "if")
    return Token::Kind::If;
  if (s == "print" || s == "println")
    return Token::Kind::Println;
  if (s == "readln")
    return Token::Kind::Readln;

  return Token::Kind::Unknown;
}

bool Token::isValidLiteral(std::string s) {
  char beg = s[0];
  char end = s[s.size() - 1];

  for (int i = 1; i < s.size() - 1; i++) {
    if (getKind(s[i]) == Kind::SingleQuote ||
        getKind(s[i]) == Kind::DoubleQuote)
      return false;
  }

  return getKind(beg) == Kind::DoubleQuote &&
         getKind(end) == Kind::DoubleQuote;
}

bool Token::isValidToken(std::string s) {
  if (std::any_of(std::begin(s), std::end(s), [](char c) {
        return !isalnum(c) && c != '_';
      })) {
    return false;
  }

  return true;
}

void Token::trimQuotes(std::string &s) {
  /**
   * If there are multiple spaces, it is likely that the
   * token was weaved using Syntax::wrapToken() and so we
   * erase the double quote along with the next space.
   */
  std::size_t count =
      std::count(std::begin(s), std::end(s), ' ');
  int cbeg = count > 1 ? 2 : 1;

  if (isValidLiteral(s)) {
    s.erase(0, cbeg);
    s.erase(s.size() - 1, 1);
    return;
  }

  throw std::invalid_argument(Error::Format(
      "Fatal: Invalid literal - %s", s.c_str()));
}
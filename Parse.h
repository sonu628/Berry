// Parse.h
//

#pragma once

/* clang-format off */
#define IF     "if"
#define ELSE   "else"
#define ENDIF  "endif"
/* clang-format on */

#include "Error.h"
#include "Signatures.h"
#include "Token.h"
#include <algorithm>
#include <unordered_set>

namespace SyntaxNS {
auto accumulate = [](const TOKENS &tokens, const int beg,
                     const int end) -> std::string {
  std::string s;
  if (Token::getKind(tokens[beg].first) ==
      Token::Kind::DoubleQuote) {
    for (int i = beg; i <= end; i++) {
      s += tokens[i].first + " ";
    }
  } else {
    s += tokens[beg].first;
  }

  return s;
};

auto assertSize = [](const int size,
                     const int req) -> void {
  if (size != req) {
    throw std::invalid_argument(Error::Format(
        "Required size: %d. Obtained size: %d.", req,
        size));
  }
};

auto assertToken = [](const Token::Kind kind,
                      const Token::Kind expect) -> void {
  if (kind != expect) {
    throw std::invalid_argument(Error::Format(
        "Expected type %d but got %d.", expect, kind));
  }
};

auto assertTokenKind = [](const TokenType type,
                          const TokenType expect) -> void {
  if (type != expect) {
    throw std::invalid_argument(Error::Format(
        "Expected type %d but got %d.", expect, type));
  }
};
} // namespace Syntax

namespace Parse {
struct Declaration {
private:
  TOKENS _tokens, _lhs, _rhs;

public:
  explicit Declaration(TOKENS tokens);
  std::string getVal(void);
  std::string getVar(void);
};

struct If {
private:
  std::string _operator;
  TOKENS _tokens, _lhs, _rhs;
  std::unordered_set<std::string> _compOps = {
      "=", "<", ">", "==", "<=", ">=", "!=", "!"};

public:
  explicit If(TOKENS tokens);
  std::string getLhs(void);
  std::string getOperator(void);
  std::string getRhs(void);
};

struct Println {
private:
  TOKENS _tokens;

public:
  Println(TOKENS tokens, SymbolTable &SymbolTable_);
  TOKENS getTokens(void);
};

struct Readln {
private:
  TOKENS _tokens;
  std::string _identifier;

public:
  explicit Readln(TOKENS tokens);
  std::string getIdentifier(void);
};
} // namespace Parse

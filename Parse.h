// Parse.h
//

#pragma once

/* clang-format off */
#define DQUOTE "\""
#define EQUAL  "="
#define IF     "if"
#define ELSE   "else"
#define ENDIF  "endif"
/* clang-format on */

#include "Signatures.h"
#include <algorithm>
#include <unordered_set>

namespace Parse {
static void Assert(int size, int req);
static void Assert(std::string found, std::string expect);
static std::string wrapToken(TOKENS tokens, int beg,
                             int end);

struct Declaration {
private:
  std::string _sep;
  TOKENS _tokens, _lhs, _rhs;

public:
  Declaration(TOKENS tokens);
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
  If(TOKENS tokens);
  std::string getLhs(void);
  std::string getOperator(void);
  std::string getRhs(void);
};

struct Println {
private:
  TOKENS _tokens;

public:
  Println(TOKENS tokens, SymbolTable &symbolTable);
  std::string getIdentifier(void);
};

struct Readln {
private:
  TOKENS _tokens;
  std::string _identifier;

public:
  Readln(TOKENS tokens);
  std::string getIdentifier(void);
};
} // namespace Parse
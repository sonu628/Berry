// Signatures.h
//

#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

enum VarType {
  Int = 1,
  String = 5,
  Boolean = 6,
  Unknown = 9
};
enum TokenType {
  Builtin = 11,
  Identifier = 12,
  Operator = 13,
  Syntax = 14,
  UnRec = 9
};

struct AstStatementNode;
struct SymbolTable;

struct Declr {
  enum VarType _type;
  std::vector<std::string> _values;
  explicit Declr(std::vector<std::string> values)
      : _type(VarType::Unknown),
        _values(std::move(values)) {}
};

#define TOKENS                                             \
  std::vector<std::pair<std::string, TokenType>>

#define SYMBOL_TBL                                         \
  std::unordered_map<std::string, std::shared_ptr<Declr>>

#define FUNC_MAP                                           \
  std::unordered_map<                                      \
      std::string, std::function<void(                     \
                       std::shared_ptr<AstStatementNode>,  \
                       SymbolTable &)>>

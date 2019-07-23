// Signatures.h
//

#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

struct AstStatementNode;
struct SymbolTable;

#define TOKENS                                             \
  std::vector<std::pair<std::string, std::string>>

#define SYMBOL_TBL                                         \
  std::unordered_map<std::string, std::string>

#define FUNC_MAP                                           \
  std::unordered_map<                                      \
      std::string, std::function<void(                     \
                       std::shared_ptr<AstStatementNode>,  \
                       SymbolTable &)>>

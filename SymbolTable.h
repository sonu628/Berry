// SymbolTable.h
//

#pragma once

#define KIND_BUILTIN_FUNC "__kindBuiltinFunc"
#define KIND_IDENTIFIER "__kindIdentifier "
#define KIND_OPERATOR "__kindOperator   "
#define KIND_SYNTAX "__kindSyntax     "
#define KIND_UK "__kindUnknown    "

#include "Signatures.h"
#include <functional>
#include <unordered_map>

struct SymbolTable {
private:
  SYMBOL_TBL _table;
  unsigned int _stackValue;

public:
  SymbolTable();
  void decrementStackValue();
  void dumpContents(void);
  unsigned int getStackValue();
  std::string getSymbolValue(std::string symbol,
                             unsigned int presQuotes);
  void incrementStackValue();
  bool recordExists(std::string symbol);
  void recordSymbol(std::string symbol, std::string value);
};
// SymbolTable.h
//

#pragma once

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
  std::string getSymbolValue(const std::string &symbol,
                             unsigned int presQuotes);
  void incrementStackValue();
  bool recordExists(const std::string &symbol);
  void recordSymbol(const std::string &symbol,
                    std::string value);
};

// SymbolTable.cpp
//

#include "SymbolTable.h"
#include "Error.h"
#include <cstring>

SymbolTable::SymbolTable() : _stackValue(0) {}

void SymbolTable::decrementStackValue(void) {
  _stackValue--;
}

void SymbolTable::dumpContents(void) {
  SYMBOL_TBL::iterator itr = std::begin(_table);
  while (itr != std::end(_table)) {
    if (itr->second.substr(0, 6) != "__kind") {
      _Console::Write("%s - %s", itr->first.c_str(),
                      itr->second.c_str());
    }

    itr++;
  }
}

unsigned int SymbolTable::getStackValue(void) {
  return _stackValue;
}

std::string
SymbolTable::getSymbolValue(std::string symbol,
                            unsigned int presQuotes) {
  if (recordExists(symbol)) {
    std::string val = _table[symbol];
    if (!presQuotes) {
      val.erase(0, 1);
      val.erase(val.size() - 1, 1);
    }

    return val;
  }

  throw std::invalid_argument(Error::Format(
      "Symbol not recorded - %s.", symbol.c_str()));
}

void SymbolTable::incrementStackValue(void) {
  _stackValue++;
}

bool SymbolTable::recordExists(std::string symbol) {
  return _table.find(symbol) != _table.end();
}

void SymbolTable::recordSymbol(std::string symbol,
                               std::string kind) {

  SYMBOL_TBL::iterator itr = _table.find(symbol);
  if (itr == std::end(_table)) {
    _table.insert({symbol, kind});
    return;
  }

  throw std::invalid_argument(Error::Format(
      "Fatal: Recording existing symbol - %s.",
      symbol.c_str()));
}
// SymbolTable.cpp
//

#include "SymbolTable.h"
#include "Error.h"

SymbolTable::SymbolTable() : _stackValue(0) {}

void SymbolTable::decrementStackValue(void) {
  _stackValue--;
}

void SymbolTable::dumpContents(void) {
  SYMBOL_TBL::iterator itr = std::begin(_table);
  /* TODO: Handle case when _values.size() > 0 */
  while (itr != std::end(_table)) {
    if (itr->second->_values[0].substr(0, 6) != "__kind") {
      _Console::Write("%s - %s", itr->first.c_str(),
                      itr->second->_values[0].c_str());
    }

    itr++;
  }
}

unsigned int SymbolTable::getStackValue(void) {
  return _stackValue;
}

std::string
SymbolTable::getSymbolValue(const std::string &symbol,
                            unsigned int presQuotes) {
  if (recordExists(symbol)) {
    auto val = _table[symbol]->_values[0];
    if (!presQuotes && static_cast<int>(val.size()) > 0) {
      val.erase(0, 1);
      val.erase(val.size() - 1, 1);
    }

    return val;
  }

  throw std::invalid_argument(
      Error::Format(Error::symbolMissing, symbol.c_str()));
}

void SymbolTable::incrementStackValue(void) {
  _stackValue++;
}

bool SymbolTable::recordExists(const std::string &symbol) {
  return _table.find(symbol) != _table.end();
}

void SymbolTable::recordSymbol(const std::string &symbol,
                               std::string kind) {

  _table[symbol] = std::make_shared<Declr>(
      std::vector<std::string>{kind});
}

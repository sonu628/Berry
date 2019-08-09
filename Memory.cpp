// Memory.cpp
//

#include "Memory.h"
#include "Error.h"
#include "Parse.h"
#include "Token.h"

void Memory::Get(std::shared_ptr<AstStatementNode> node,
                 SymbolTable &symbolTable) {

  std::shared_ptr<AstReadNode> ReadNode =
      std::dynamic_pointer_cast<AstReadNode>(node);
  std::string symbol = ReadNode->getIdentifier();

  if (symbolTable.recordExists(symbol)) {
    throw std::invalid_argument(Error::Format(
        "Fatal: Symbol \"%s\" is already recorded.",
        symbol.c_str()));
  }

  std::string val;
  std::cin >> val;
  symbolTable.recordSymbol(symbol, "\"" + val + "\"");
}

void Memory::Let(std::shared_ptr<AstStatementNode> node,
                 SymbolTable &symbolTable) {

  std::shared_ptr<AstDeclrNode> DeclrNode =
      std::dynamic_pointer_cast<AstDeclrNode>(node);
  std::string symbol = DeclrNode->getVar();
  std::string value = DeclrNode->getVal();

  if (Token::getKind(value[0]) !=
      Token::Kind::DoubleQuote) {
    value = symbolTable.getSymbolValue(value, 1);
  }

  if (value.substr(1, 6) == "__kind") {
    throw std::invalid_argument(
        Error::Format(Error::reservedValue, value.c_str()));
  }

  symbolTable.recordSymbol(symbol, value);
}

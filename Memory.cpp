// Memory.cpp
//

#include "Memory.h"
#include "Error.h"
#include "Parse.h"
#include "Token.h"

void Memory::Get(const std::shared_ptr<AstStatementNode>& node,
                 SymbolTable &SymbolTable_) {

  std::shared_ptr<AstReadNode> ReadNode =
      std::dynamic_pointer_cast<AstReadNode>(node);
  std::string symbol = ReadNode->getIdentifier();

  if (SymbolTable_.recordExists(symbol)) {
    throw std::invalid_argument(Error::Format(
        "Fatal: Symbol \"%s\" is already recorded.",
        symbol.c_str()));
  }

  std::string val;
  std::cin >> val;
  SymbolTable_.recordSymbol(symbol, "\"" + val + "\"");
}

void Memory::Let(const std::shared_ptr<AstStatementNode>& node,
                 SymbolTable &SymbolTable_) {

  std::shared_ptr<AstDeclrNode> DeclrNode =
      std::dynamic_pointer_cast<AstDeclrNode>(node);
  std::string symbol = DeclrNode->getVar();
  std::string value = DeclrNode->getVal();
  const int klen = static_cast<int>(value.size());

  if (klen > 0 && Token::getKind(value[0]) !=
                      Token::Kind::DoubleQuote) {
    value = SymbolTable_.getSymbolValue(value, 1);
  }

  SymbolTable_.recordSymbol(symbol, value);
}

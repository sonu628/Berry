// Bind.cpp
//

#include "Bind.h"
#include "AST.h"
#include "Console.h"
#include "Error.h"
#include "Evaluator.h"
#include <algorithm>

Bind::Bind(SymbolTable &symbolTable)
    : _SymbolTable(symbolTable) {
  _fmap.insert({"if", Evaluator::Evaluate});
  _fmap.insert({"let", Memory::Let});
  _fmap.insert({"var", Memory::Let});
  _fmap.insert({"print", Console::println});
  _fmap.insert({"println", Console::println});
  _fmap.insert({"readln", Memory::Get});
}

void Bind::invokeNode(
    std::shared_ptr<AstStatementNode> node) {
  std::string keyword =
      std::begin(node->getTokens())->first;

  FUNC_MAP::iterator itr = _fmap.find(keyword);
  if (itr != std::end(_fmap)) {
    unsigned int stackVal = _SymbolTable.getStackValue();
    (*itr).second(node, _SymbolTable);

    if (_SymbolTable.getStackValue() > stackVal) {
      for (std::shared_ptr<AstStatementNode> lnode :
           node->_body) {
        invokeNode(lnode);
      }
    } else {
      for (std::shared_ptr<AstStatementNode> rnode :
           node->_alt) {
        invokeNode(rnode);
      }
    }

  } else {
    throw std::invalid_argument(Error::Format(
        Error::invalidKeyword, keyword.c_str()));
  }
}

unsigned int Bind::invokeAllNodes(
    std::vector<std::shared_ptr<AstStatementNode>> body) {
  unsigned int nodeCount = 0;
  for (std::shared_ptr<AstStatementNode> node : body) {
    nodeCount++;
    try {
      invokeNode(node);
    } catch (std::exception &e) {
      _Console::Write(Error::errorInLine, nodeCount,
                      e.what());
      return 1;
    }
  }

  return 0;
}

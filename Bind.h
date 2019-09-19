// Bind.h
//

#pragma once

#include "Memory.h"
#include "Signatures.h"
#include "SymbolTable.h"
#include <memory>

struct Bind {
private:
  FUNC_MAP _fmap;
  SymbolTable &_SymbolTable;

public:
  explicit Bind(SymbolTable &SymbolTable_);
  void invokeNode(const std::shared_ptr<AstStatementNode>& node);
  unsigned int invokeAllNodes(
      const std::vector<std::shared_ptr<AstStatementNode>>& body);
};
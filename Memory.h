// Memory.h
//

#pragma once

#include "AST.h"
#include "SymbolTable.h"

namespace Memory {
void Get(const std::shared_ptr<AstStatementNode>& node,
         SymbolTable &SymbolTable_);
void Let(const std::shared_ptr<AstStatementNode>& node,
         SymbolTable &SymbolTable_);
} // namespace Memory
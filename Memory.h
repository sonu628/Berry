// Memory.h
//

#pragma once

#include "AST.h"
#include "SymbolTable.h"

namespace Memory {
void Get(std::shared_ptr<AstStatementNode> node,
         SymbolTable &symbolTable);
void Let(std::shared_ptr<AstStatementNode> node,
         SymbolTable &symbolTable);
} // namespace Memory
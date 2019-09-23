// Console.h
//

#pragma once

#include "AST.h"
#include "SymbolTable.h"

namespace Console {
void println(const std::shared_ptr<AstStatementNode>& node,
             SymbolTable &SymbolTable_);
} // namespace Console
// Console.h
//

#pragma once

#include "AST.h"
#include "SymbolTable.h"

namespace Console {
void println(std::shared_ptr<AstStatementNode> node,
             SymbolTable &symbolTable);
} // namespace Console
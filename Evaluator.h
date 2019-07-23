// Evaluator.h
//

#pragma once

#include "AST.h"
#include "SymbolTable.h"
#include <memory>

namespace Evaluator {
void Evaluate(std::shared_ptr<AstStatementNode> node,
              SymbolTable &symbolTable);
} // namespace Evaluator
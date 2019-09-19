// Evaluator.h
//

#pragma once

#include "AST.h"
#include "SymbolTable.h"
#include <memory>

namespace Evaluator {
void Evaluate(const std::shared_ptr<AstStatementNode>& node,
              SymbolTable &SymbolTable_);
} // namespace Evaluator
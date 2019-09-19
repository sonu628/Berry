// Evaluator.cpp
//

#include "Evaluator.h"
#include "AST.h"
#include "Parse.h"
#include "Token.h"

void Evaluator::Evaluate(
    const std::shared_ptr<AstStatementNode>& node,
    SymbolTable &SymbolTable_) {

  std::shared_ptr<AstIfNode> IfNode =
      std::dynamic_pointer_cast<AstIfNode>(node);
  std::string symbol = IfNode->getLhs();
  std::string value = IfNode->getRhs();

  std::string actualValue =
      SymbolTable_.getSymbolValue(symbol, 1);

  switch (Token::getKind(IfNode->getOperator())) {
  case Token::Kind::Comparison: {
    if (value == actualValue) {
      SymbolTable_.incrementStackValue();
    }

    break;
  }

  case Token::Kind::NotEqualTo: {
    if (value != actualValue) {
      SymbolTable_.incrementStackValue();
    }

    break;
  }

  // to silence warnings
  default:;
  }
}
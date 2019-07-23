// Evaluator.cpp
//

#include "Evaluator.h"
#include "AST.h"
#include "Error.h"
#include "Parse.h"
#include "Token.h"

void Evaluator::Evaluate(
    std::shared_ptr<AstStatementNode> node,
    SymbolTable &symbolTable) {

  std::shared_ptr<AstIfNode> IfNode =
      std::dynamic_pointer_cast<AstIfNode>(node);
  std::string symbol = IfNode->getLhs();
  std::string value = IfNode->getRhs();

  std::string actualValue =
      symbolTable.getSymbolValue(symbol, 1);

  switch (Token::getKind(IfNode->getOperator())) {
  case Token::Kind::Comparison: {
    if (value == actualValue) {
      symbolTable.incrementStackValue();
    }

    break;
  }

  case Token::Kind::NotEqualTo: {
    if (value != actualValue) {
      symbolTable.incrementStackValue();
    }

    break;
  }

  // to silence warnings
  default:;
  }
}
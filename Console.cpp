// Console.cpp
//

#include "Console.h"
#include "Error.h"
#include "Parse.h"
#include "Token.h"

void Console::println(
    std::shared_ptr<AstStatementNode> node,
    SymbolTable &symbolTable) {

  std::shared_ptr<AstPrintNode> PrintNode =
      std::dynamic_pointer_cast<AstPrintNode>(node);
  std::string idf = PrintNode->getIdentifier(), val;

  val = Token::getKind(idf[0]) == Token::Kind::DoubleQuote
            ? idf
            : symbolTable.getSymbolValue(idf, 0);

  if (Token::isValidLiteral(val)) {
    Token::trimQuotes(val);
  }

  _Console::Write("%s", val.c_str());
}
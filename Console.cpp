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
  std::string val;
  TOKENS tokens = PrintNode->getTokens();

  if (static_cast<int>(tokens.size()) == 2) {
    /**
     * print[ln] <token_1>
     *            ^^^^^^^ most likely to be a var.
     */
    val = tokens[1].first;
    if (static_cast<int>(val.size()) > 0 &&
        Token::getKind(val[0]) == Token::Kind::Dollar) {
      val.erase(0, 1);
    }

    val = symbolTable.getSymbolValue(val, 0);
  } else {
    std::for_each(
        ++std::begin(tokens), std::end(tokens),
        [&symbolTable,
         &val](std::pair<std::string, std::string> p) {
          std::string s = p.first;
          
          if (static_cast<int>(s.size()) > 0 &&
              Token::getKind(s[0]) == Token::Kind::Dollar) {
            s.erase(0, 1);
            val += symbolTable.getSymbolValue(s, 0) + " ";
          } else {
            val += s + " ";
          }
        });
  }

  if (Token::isValidLiteral(val)) {
    Token::trimQuotes(val);
  }

  _Console::Write("%s", val.c_str());
}

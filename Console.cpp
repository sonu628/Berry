// Console.cpp
//

#include "Console.h"
#include "Error.h"
#include "Parse.h"
#include "Token.h"

void Console::println(
    const std::shared_ptr<AstStatementNode> &node,
    SymbolTable &SymbolTable_) {

  std::shared_ptr<AstPrintNode> PrintNode =
      std::dynamic_pointer_cast<AstPrintNode>(node);

  std::string val;
  TOKENS tokens = PrintNode->getTokens();
  tokens.erase(std::begin(tokens));

  for (const auto &p : tokens) {
    if (Token::getKind(p.first) == Token::Kind::DoubleQuote) {
      continue;
    }

    std::string token = p.first + " ";

    switch (Token::getKind(token[0])) {
    case Token::Kind::Dollar:
      token.erase(0, 1);
      token.erase(token.size() - 1, 1);
      val += SymbolTable_.getSymbolValue(token, 0);
      break;

    case Token::Kind::DoubleQuote:
      token.erase(0, 1);
      val += token;
      break;

    default:
      if (static_cast<int>(tokens.size()) > 1) {
        val += token;
        break;
      } else {
        throw std::invalid_argument(Error::Format(
            Error::invalidFormatting, token.c_str()));
      }
    }
  }

  _Console::Write("%s", val.c_str());
}

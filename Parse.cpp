// Parse.cpp
//

#include "Parse.h"
#include "SymbolTable.h"
#include <algorithm>
#include <cassert>
#include <utility>

Parse::Declaration::Declaration(TOKENS tokens)
    : _tokens(std::move(tokens)) {
  std::copy(std::begin(_tokens), std::begin(_tokens) + 2,
            std::back_inserter(_lhs));

  /* No value for var provided */
  if (static_cast<int>(_tokens.size()) == 2) {
    return;
  }

  SyntaxNS::assertToken(Token::getKind(_tokens[2].first),
                        Token::Kind::EqualTo);

  bool isLiteral = Token::getKind(_tokens[3].first) ==
                   Token::Kind::DoubleQuote;
  TOKENS::iterator itr = std::begin(_tokens) + 3;

  while (itr != std::end(_tokens)) {
    _rhs.push_back(*itr);
    itr++;
  }

  if (!isLiteral) {
    SyntaxNS::assertSize(_rhs.size(), 1);
  }
}

std::string Parse::Declaration::getVal(void) {
  return static_cast<int>(_tokens.size()) == 2
             ? ""
             : SyntaxNS::accumulate(_tokens, 3, 5);
}

std::string Parse::Declaration::getVar(void) {
  return _tokens[1].first;
}

Parse::If::If(TOKENS tokens) : _tokens(std::move(tokens)) {
  TOKENS::iterator itr = std::begin(_tokens) + 2;
  std::string c1 = (*itr).first;
  std::string c2 = (*(itr + 1)).first;
  _operator = _compOps.find(c2) != std::end(_compOps)
                  ? c1 + c2
                  : c1;

  assert(_compOps.find(_operator) != std::end(_compOps) &&
         _operator.size() == 2);
  std::copy(std::begin(_tokens), itr,
            std::back_inserter(_lhs));
  std::copy(++(++itr), std::end(_tokens),
            std::back_inserter(_rhs));

  if (Token::getKind(_tokens[4].first) !=
      Token::Kind::DoubleQuote) {
    SyntaxNS::assertSize(static_cast<int>(_rhs.size()), 4);
  }
}

std::string Parse::If::getLhs(void) {
  return SyntaxNS::accumulate(_lhs, 1, 3);
}

std::string Parse::If::getOperator(void) {
  return _operator;
}

std::string Parse::If::getRhs(void) {
  return SyntaxNS::accumulate(_rhs, 0, 2);
}

Parse::Println::Println(TOKENS tokens,
                        SymbolTable &SymbolTable_)
    : _tokens(tokens) {
  /**
   * See what we're going to be writing to the console.
   * Is it a string literal? If yes, does it begin with a
   * double quote?
   */
  if (Token::getKind(_tokens[1].first[0]) !=
      Token::Kind::DoubleQuote) {
    /* If not, we should be expecting only 1 token. */
    SyntaxNS::assertSize(static_cast<int>(_tokens.size()),
                         2);
  }
}

TOKENS Parse::Println::getTokens(void) { return _tokens; }

Parse::Readln::Readln(TOKENS tokens)
    : _tokens(tokens), _identifier(tokens[1].first) {
  assert(Token::isValidToken(tokens[1].first));
  SyntaxNS::assertSize(static_cast<int>(tokens.size()), 2);
}

std::string Parse::Readln::getIdentifier(void) {
  return _identifier;
}

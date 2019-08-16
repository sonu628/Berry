// Parse.cpp
//

#include "Parse.h"
#include "Error.h"
#include "SymbolTable.h"
#include "Token.h"
#include <algorithm>
#include <cassert>

void Parse::Assert(int size, int req) {
  /**
   * This func helps in asserting that we've received
   * exactly the required number of tokens, not more,
   * not less.
   */
  if (size != req) {
    throw std::invalid_argument(Error::Format(
        "Required size: %d. Obtained size: %d.", req,
        size));
  }
}

void Parse::Assert(std::string found, std::string expect) {
  /**
   * Chances are that we come across a token that we're
   * expecting a certain token, but receive something else.
   * This func generates the required error in such case.
   */
  if (found != expect) {
    throw std::invalid_argument(
        Error::Format("Expected %s but got %s.",
                      expect.c_str(), found.c_str()));
  }
}

std::string Parse::wrapToken(TOKENS tokens, int beg,
                             int end) {
  /**
   * Certain tokens need to be grouped together when
   * processing. For example, a token might require to
   * be wrapped in double quotes. This happens because
   * we treat double quote as a separate token.
   *
   * This func helps reduce the boiler plate code and
   * quickly wrap tokens, indicated by 'beg' and 'end'.
   *
   * Wrapping range - [beg, end]
   */
  std::string s;
  if (Token::getKind(tokens[beg].first) ==
      Token::Kind::DoubleQuote) {
    for (int i = beg; i <= end; i++) {
      s += tokens[i].first;
    }
  } else {
    s += tokens[beg].first;
  }

  return s;
}

Parse::Declaration::Declaration(TOKENS tokens)
    : _tokens(tokens) {

  /**
   * Statements that start with 'let' or 'var' are called
   * declarative statements.
   *
   * This class helps in parsing the declaration statements.
   *
   * TODO: Make sure that 'var' and 'val' qualify the naming
   * rules.
   */
  _sep = EQUAL;
  if (static_cast<int>(tokens.size()) == 2) {
    TOKENS::iterator beg = std::begin(tokens);
    TOKENS::iterator end = std::begin(tokens) + 2;
    std::copy(beg, end, std::back_inserter(_lhs));
    return;
  }

  Parse::Assert(_tokens[2].first, EQUAL);
  Parse::Assert(_tokens[2].second, KIND_OPERATOR);

  TOKENS::iterator itr = std::begin(_tokens) + 2;
  assert(itr != std::end(_tokens));

  /**
   * We partition the statement into 2 halves. lhs & rhs.
   * lhs - consists of tokens 'let/var' followed by 'var'.
   * rhs - 'val'.
   */
  std::copy(std::begin(_tokens), --itr,
            std::back_inserter(_lhs));
  itr++;
  std::copy(++itr, std::end(_tokens),
            std::back_inserter(_rhs));

  /**
   * 'var' might be another variable. If that's the case,
   * we do not expect that the token 'var' will be
   * surrounded by double quotes.
   */
  if (Token::getKind(tokens[3].first) ==
      Token::Kind::DoubleQuote) {
    /**
     * 'var' is surrounded by double quotes.
     * Note that we do not need to check for closing quote
     * as Lexer has already taken care of that.
     */
    Parse::Assert(static_cast<int>(tokens.size()), 6);
    Parse::Assert(tokens[5].first, DQUOTE);
    Parse::Assert(tokens[5].second, KIND_SYNTAX);
  } else {
    Parse::Assert(static_cast<int>(tokens.size()), 4);
  }
}

std::string Parse::Declaration::getVal(void) {
  return static_cast<int>(_tokens.size()) == 2
             ? ""
             : Parse::wrapToken(_tokens, 3, 5);
}

std::string Parse::Declaration::getVar(void) {
  return _tokens[1].first;
}

Parse::If::If(TOKENS tokens) : _tokens(tokens) {
  TOKENS::iterator itr = std::begin(_tokens) + 2;
  std::string tk = (*itr).first;

  /**
   * We split the comparison operator into 2 tokens
   * Eg: == is split as '=' & '='.
   *     <= is split as '<' & '='.
   */
  for (int i = 0; i < 2; i++) {
    std::string tk = (*(itr + i)).first;
    if (_compOps.find(tk) != std::end(_compOps))
      _operator += tk;
  }

  /* Did we get it right? */
  assert(_compOps.find(_operator) != std::end(_compOps) &&
         _operator.size() == 2);
  /**
   * Just like Parse::Declaration, we split the tokens into
   * lhs & rhs.
   */
  std::copy(std::begin(_tokens), itr,
            std::back_inserter(_lhs));
  itr++;
  std::copy(++itr, std::end(_tokens),
            std::back_inserter(_rhs));

  /* Run the usual drill, for both with & without quotes */
  if (Token::getKind(tokens[4].first) ==
      Token::Kind::DoubleQuote) {
    Parse::Assert(static_cast<int>(tokens.size()), 7);
    Parse::Assert(tokens[6].first, DQUOTE);
    Parse::Assert(tokens[6].second, KIND_SYNTAX);
  } else {
    Parse::Assert(static_cast<int>(tokens.size()), 4);
  }
}

std::string Parse::If::getLhs(void) {
  return Parse::wrapToken(_lhs, 1, 3);
}

std::string Parse::If::getOperator(void) {
  return _operator;
}

std::string Parse::If::getRhs(void) {
  return Parse::wrapToken(_rhs, 0, 2);
}

Parse::Println::Println(TOKENS tokens,
                        SymbolTable &symbolTable)
    : _tokens(tokens) {
  /**
   * See what we're going to be writing to the console.
   * Is it a string literal? If yes, does it begin with a
   * double quote?
   */
  if (Token::getKind(tokens[1].first[0]) !=
      Token::Kind::DoubleQuote) {
    /* If not, we should be expecting only 1 token. */
    Parse::Assert(static_cast<int>(tokens.size()), 2);
  }
}

TOKENS Parse::Println::getTokens(void) { return _tokens; }

Parse::Readln::Readln(TOKENS tokens)
    : _tokens(tokens), _identifier(tokens[1].first) {
  assert(Token::isValidToken(tokens[1].first));
  Parse::Assert(static_cast<int>(tokens.size()), 2);
}

std::string Parse::Readln::getIdentifier(void) {
  return _identifier;
}

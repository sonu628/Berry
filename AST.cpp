// AST.cpp
//

#include "AST.h"
#include "Error.h"
#include "Token.h"

TOKENS AstStatementNode::getTokens(void) { return _tokens; }

AstDeclrNode::AstDeclrNode(const TOKENS &tokens)
    : Parse::Declaration(tokens), _tokens(tokens) {
  _val = Parse::Declaration::getVal();
  _var = Parse::Declaration::getVar();
}

TOKENS AstDeclrNode::getTokens(void) { return _tokens; }

DummyNode::DummyNode(const TOKENS &tokens) {}

AstIfNode::AstIfNode(const TOKENS &tokens)
    : Parse::If(tokens), _tokens(tokens) {
  _lhs = Parse::If::getLhs();
  _rhs = Parse::If::getRhs();
  _operator = Parse::If::getOperator();
}

TOKENS AstIfNode::getTokens(void) { return _tokens; }

AstPrintNode::AstPrintNode(const TOKENS &tokens,
                           SymbolTable &SymbolTable_)
    : Parse::Println(tokens, SymbolTable_),
      _tokens(tokens) {}

TOKENS AstPrintNode::getTokens(void) { return _tokens; }

AstReadNode::AstReadNode(const TOKENS &tokens)
    : Parse::Readln(tokens), _tokens(tokens) {
  _identifier = Parse::Readln::getIdentifier();
}

TOKENS AstReadNode::getTokens(void) { return _tokens; }

AST::AST(SymbolTable &SymbolTable_)
    : _lr(0), _SymbolTable(SymbolTable_) {}

void AST::appendNode(const TOKENS &tokens) {
  if (static_cast<int>(tokens.size()) == 0) {
    return;
  }

  auto isBranch = [](const std::string &keyword) -> bool {
    return keyword == IF || keyword == ELSE ||
           keyword == ENDIF;
  };

  std::shared_ptr<AstStatementNode> node =
      AST::toAstNodeType(tokens, _SymbolTable);
  std::string keyword = std::begin(tokens)->first;

  if (static_cast<int>(_stack.size()) == 0) {
    if (!isBranch(keyword)) {
      _body.push_back(node);
      return;
    }

    if (keyword == IF) {
      _lr = 1;
      _body.push_back(node);
      _stack.push(node);
      return;
    }

    throw std::invalid_argument(Error::Format(
        "Fatal: Invalid keyword without \"if\".",
        keyword.c_str()));
  }

  /* _stack is not empty */
  if (keyword == IF) {
    std::shared_ptr<AstStatementNode> tail = _stack.top();
    tail->_body.push_back(node);
    _stack.push(node);
    return;
  }

  if (keyword == ELSE) {
    _lr = -1;
    return;
  }

  if (keyword == ENDIF) {
    _lr = 1;
    _stack.pop();
    return;
  }

  std::shared_ptr<AstStatementNode> tail = _stack.top();
  _lr == 1 ? tail->_body.push_back(node)
           : tail->_alt.push_back(node);
}

void AST::dumpSymbolTable(void) {
  _SymbolTable.dumpContents();
}

void AST::dumpSyntaxTree(void) { _visitNodes(_body); }

std::vector<std::shared_ptr<AstStatementNode>>
AST::getProgramBody(void) {
  return _body;
}

std::shared_ptr<AstStatementNode>
AST::toAstNodeType(const TOKENS &tokens,
                   SymbolTable &SymbolTable_) {
  switch (Token::getKind(tokens[0].first)) {
  case Token::Kind::Declr:
    return std::make_shared<AstDeclrNode>(tokens);

  /* We don't really care about else & endif */
  case Token::Kind::Else:
  case Token::Kind::Endif:
    return std::make_shared<DummyNode>(tokens);

  case Token::Kind::If:
    return std::make_shared<AstIfNode>(tokens);
  case Token::Kind::Println:
    return std::make_shared<AstPrintNode>(tokens,
                                          SymbolTable_);
  case Token::Kind::Readln:
    return std::make_shared<AstReadNode>(tokens);
    /* To silence warnings */
  default:;
  }

  throw std::invalid_argument(Error::Format(
      "Invalid instruction - %s", tokens[0].first.c_str()));
}

bool AST::verifyGoodProgram(void) {
  return static_cast<int>(_stack.size()) == 0;
}

void AST::_visitNodes(
    const std::vector<std::shared_ptr<AstStatementNode>>& vec) {

  for (const std::shared_ptr<AstStatementNode>& node : vec) {
    if (!node) {
      continue;
    }

    const TOKENS &tokens = node->getTokens();
    auto itr = tokens.begin();
    std::cout << "|- " << itr++->first << std::endl;

    while (itr != tokens.end()) {
      std::cout << " |- " << itr->first << " "
                << itr++->second << std::endl;
    }

    _visitNodes(node->_body);
    _visitNodes(node->_alt);
  }
}

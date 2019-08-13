// AST.h
//

#pragma once

#include "Parse.h"
#include "Signatures.h"
#include "SymbolTable.h"
#include <memory>
#include <stack>
#include <vector>

struct AstStatementNode {
private:
  TOKENS _tokens;

public:
  std::vector<std::shared_ptr<AstStatementNode>> _alt,
      _body;
  virtual TOKENS getTokens(void);
};

struct AstDeclrNode : public AstStatementNode,
                      Parse::Declaration {
private:
  TOKENS _tokens;
  std::string _val, _var;

public:
  AstDeclrNode(TOKENS tokens);
  TOKENS getTokens(void);
};

struct DummyNode : public AstStatementNode {
public:
  DummyNode(TOKENS tokens);
};

struct AstIfNode : public AstStatementNode, Parse::If {
private:
  TOKENS _tokens;
  std::string _operator, _lhs, _rhs;

public:
  AstIfNode(TOKENS tokens);
  TOKENS getTokens(void);
};

struct AstPrintNode : public AstStatementNode,
                      Parse::Println {
private:
  TOKENS _tokens;

public:
  AstPrintNode(TOKENS tokens, SymbolTable &SymbolTable_);
  TOKENS getTokens(void);
};

struct AstReadNode : public AstStatementNode,
                     Parse::Readln {
private:
  TOKENS _tokens;
  std::string _identifier;

public:
  AstReadNode(TOKENS tokens);
  TOKENS getTokens(void);
};

/* Always at last */
struct AST {
private:
  unsigned int _lr;
  SymbolTable &_SymbolTable;
  std::stack<std::shared_ptr<AstStatementNode>> _stack;
  std::vector<std::shared_ptr<AstStatementNode>> _body;
  void _visitNodes(
      std::vector<std::shared_ptr<AstStatementNode>> vec);

public:
  AST(SymbolTable &SymbolTable_);
  void appendNode(TOKENS tokens);
  void dumpSymbolTable(void);
  void dumpSyntaxTree(void);
  std::vector<std::shared_ptr<AstStatementNode>>
  getProgramBody(void);
  static std::shared_ptr<AstStatementNode>
  toAstNodeType(TOKENS tokens, SymbolTable &SymbolTable_);
  bool verifyGoodProgram();
};

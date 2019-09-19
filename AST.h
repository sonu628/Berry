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
  explicit AstDeclrNode(const TOKENS &tokens);
  TOKENS getTokens(void) override;
};

struct DummyNode : public AstStatementNode {
public:
  explicit DummyNode(const TOKENS &tokens);
};

struct AstIfNode : public AstStatementNode, Parse::If {
private:
  TOKENS _tokens;
  std::string _operator, _lhs, _rhs;

public:
  explicit AstIfNode(const TOKENS &tokens);
  TOKENS getTokens(void) override;
};

struct AstPrintNode : public AstStatementNode,
                      Parse::Println {
private:
  TOKENS _tokens;

public:
  AstPrintNode(const TOKENS &tokens,
               SymbolTable &SymbolTable_);
  TOKENS getTokens(void) override;
};

struct AstReadNode : public AstStatementNode,
                     Parse::Readln {
private:
  TOKENS _tokens;
  std::string _identifier;

public:
  explicit AstReadNode(const TOKENS &tokens);
  TOKENS getTokens(void) override;
};

/* Always at last */
struct AST {
private:
  unsigned int _lr;
  SymbolTable &_SymbolTable;
  std::stack<std::shared_ptr<AstStatementNode>> _stack;
  std::vector<std::shared_ptr<AstStatementNode>> _body;
  static void _visitNodes(
      const std::vector<std::shared_ptr<AstStatementNode>>& vec);

public:
  explicit AST(SymbolTable &SymbolTable_);
  void appendNode(const TOKENS &tokens);
  void dumpSymbolTable(void);
  void dumpSyntaxTree(void);
  std::vector<std::shared_ptr<AstStatementNode>>
  getProgramBody(void);
  static std::shared_ptr<AstStatementNode>
  toAstNodeType(const TOKENS &tokens,
                SymbolTable &SymbolTable_);
  bool verifyGoodProgram();
};

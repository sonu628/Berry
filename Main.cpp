// Main.cpp
//

#include "AST.h"
#include "ArgParser.h"
#include "Bind.h"
#include "Lexer.h"
#include "SymbolTable.h"
#include <cassert>
#include <iostream>
#include <string>

void dumpHeaders(void) {
  std::cout << "Berry Beta" << std::endl
            << "Author: Pawan Kartik" << std::endl
            << std::endl;
}

int main(int argc, char **argv) {
  SymbolTable SymbolTable_;
  Bind Bind_(SymbolTable_);
  AST AST_(SymbolTable_);

  Args Args_(AST_);
  Args_.collect(argc, argv);

  bool isFileProvided = argc >= 2 ? true : false;
  std::string sourceFile = isFileProvided ? argv[1] : "";
  Lexer Lexer_(sourceFile, SymbolTable_);

  if (isFileProvided) {
    assert(Lexer_.openFile());
    while (Lexer_.readLine()) {
      AST_.appendNode(Lexer_.tokenize());
    }
  } else {
    dumpHeaders();
    std::string line;
    std::cout << "> ";
    std::getline(std::cin, line);

    while (line.size()) {
      Lexer_.setLine(line);
      AST_.appendNode(Lexer_.tokenize());
      std::cout << "> ";
      std::getline(std::cin, line);
    }
    std::cout << std::endl << "Executing -" << std::endl;
  }

  assert(AST_.verifyGoodProgram());
  Args_.process();
  return Bind_.invokeAllNodes(AST_.getProgramBody());
}
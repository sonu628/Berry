// ArgParser.cpp
//

#include "ArgParser.h"
#include <algorithm>

Args::Args(AST &AST_) : _AST(AST_) {}
void Args::collect(int argc, char **argv) {
  for (int i = 2; i < argc; i++) {
    _args.push_back(argv[i]);
  }
}

bool Args::isArgPresent(std::string arg) {
  std::vector<std::string>::iterator itr =
      std::find(std::begin(_args), std::end(_args), arg);
  return itr != std::end(_args);
}

void Args::process(void) {
  for (std::string arg : _args) {
    if (arg == "--symbol-table")
      _AST.dumpSymbolTable();

    if (arg == "--syntax-tree")
      _AST.dumpSyntaxTree();
  }
}
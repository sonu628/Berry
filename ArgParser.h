// ArgPaser.h
//

#pragma once

#include "AST.h"
#include <iostream>
#include <vector>

struct Args {
private:
  AST &_AST;
  std::vector<std::string> _args;

public:
  explicit Args(AST &AST_);
  void collect(int argc, char **argv);
  bool isArgPresent(const std::string& arg);
  void process(void);
};
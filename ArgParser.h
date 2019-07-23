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
  Args(AST &AST_);
  void collect(int argc, char **argv);
  bool isArgPresent(std::string arg);
  void process(void);
};
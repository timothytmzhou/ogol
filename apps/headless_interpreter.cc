#include "core/interpreter.h"
#include <iostream>

using ogol::core::base_env;
using ogol::core::Interpreter;
using std::ifstream;

int main() {
  Interpreter interpreter;
  ifstream source("/home/timothy/Documents/main.ogl");
  source >> interpreter;
  std::cout << base_env.turtle.str();
  interpreter.Run();
}

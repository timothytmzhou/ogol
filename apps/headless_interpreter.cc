#include "core/interpreter.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using ogol::core::Interpreter;
using ogol::core::base_env;

int main() {
  Interpreter interpreter;
  ifstream source("/home/timothy/Documents/main.ogl");
  while (true) {
    source >> interpreter;
    std::cout << base_env.turtle.str();
    interpreter.Run();
  }
}
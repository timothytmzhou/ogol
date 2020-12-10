#include "core/interpreter.h"
#include <iostream>

using ogol::core::Interpreter;
using std::ifstream;

int main() {
  Turtle turtle;
  Interpreter interpreter;
  ifstream source("/home/timothy/Documents/main.ogl");
  source >> interpreter;
  std::cout << turtle.str();
  interpreter.Run(&turtle);
}

#include "core/interpreter.h"
#include <iostream>

using ogol::core::Interpreter;
using std::ifstream;

int main() {
  Turtle turtle;
  Interpreter interpreter(&turtle);
  ifstream source("/home/timothy/Documents/main.ogl");
  source >> interpreter;
  std::cout << interpreter.GetTurtle().str();
  interpreter.Run();
}

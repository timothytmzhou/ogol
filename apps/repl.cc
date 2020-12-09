#include "core/interpreter.h"
#include "visualizer/turtle.h"
#include <iostream>

using ogol::core::Interpreter;

int main() {
  Turtle turtle;
  Interpreter interpreter(&turtle);
  while (true) {
    string input;
    getline(std::cin, input);
    std::stringstream(input) >> interpreter;
    interpreter.Run();
    std::cout << interpreter.GetTurtle().str();
  }
}
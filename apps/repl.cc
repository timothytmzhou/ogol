#include "core/interpreter.h"
#include "visualizer/turtle.h"
#include <iostream>

using ogol::core::Interpreter;

int main() {
  Turtle turtle;
  Interpreter interpreter;
  while (true) {
    string input;
    getline(std::cin, input);
    std::stringstream(input) >> interpreter;
    interpreter.Run(&turtle);
    std::cout << turtle.str();
  }
}
#include "core/interpreter.h"
#include <iostream>

using ogol::core::Interpreter;

int main() {
  Interpreter interpreter;
  while (true) {
    string input;
    getline(std::cin, input);
    std::stringstream(input) >> interpreter;
    interpreter.Run();
  }
}
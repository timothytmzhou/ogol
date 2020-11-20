#include "core/interpreter.h"
#include <fstream>
#include <iostream>

using ogol::core::Interpreter;

int main() {
  Interpreter interpreter;
  while (true) {
    string source;
    std::getline(std::cin, source);
    source >> interpreter;
  }
}
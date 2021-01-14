#include "core/interpreter.h"
#include "core/lexer.h"
#include "core/parser.h"

using ogol::core::Env;
using ogol::core::Lexer;
using ogol::core::Parser;

namespace ogol::core {

Interpreter::Interpreter() : env_(nullptr, kBuiltIns) {}

std::istream &operator>>(std::istream &input,
                         ogol::core::Interpreter &interpreter) {
  std::stringstream ss;
  ss << input.rdbuf();
  interpreter.source_ = ss.str();
  return input;
}

std::istream &operator<<(ogol::core::Interpreter &interpreter,
                         std::istream &input) {
  return input >> interpreter;
}

void Interpreter::Run(Turtle *turtle) {
  Lexer lexer(source_);
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  parser.parse().Eval(&env_, turtle);
}

} // namespace ogol::core

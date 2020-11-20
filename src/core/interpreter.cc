#include "core/interpreter.h"
#include "core/lexer.h"
#include "core/parser.h"

using ogol::core::Lexer;
using ogol::core::Parser;

namespace ogol::core {

std::istream &operator>>(std::istream &input,
                         ogol::core::Interpreter &interpreter) {
  Lexer lexer;
  input >> lexer;
  interpreter.Run(lexer);
  return input;
}

std::istream &operator<<(ogol::core::Interpreter &interpreter,
                         std::istream &input) {
  Lexer lexer;
  input >> lexer;
  interpreter.Run(lexer);
  return input;
}

string &operator>>(const string &input, Interpreter &interpreter) {
  Lexer lexer;
  input >> lexer;
  interpreter.Run(lexer);
  return const_cast<string &>(input);
}

string &operator<<(Interpreter &interpreter, const string &input) {
  Lexer lexer;
  input >> lexer;
  interpreter.Run(lexer);
  return const_cast<string &>(input);
}

void Interpreter::Run(Lexer lexer) {
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  parser.parse().Eval(main_env);
}

} // namespace ogol::core

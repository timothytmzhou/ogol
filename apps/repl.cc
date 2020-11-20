#include "core/env.h"
#include "core/lexer.h"
#include "core/parser.h"
#include "core/procedures.h"
#include "core/s_expr.h"
#include <iostream>

using ogol::core::Atom;

int main() {
  static ogol::core::Env main_env(nullptr,
                                  map<string, ogol::core::SExpr>{
                                      {"print", Atom(ogol::core::Print)},
                                      {"define", Atom(ogol::core::Define)},
                                      {"+", Atom(ogol::core::Add)},
                                      {"-", Atom(ogol::core::Sub)},
                                      {"*", Atom(ogol::core::Mul)},
                                      {"/", Atom(ogol::core::Div)},
                                  });

  ogol::core::Lexer lexer;
  "(print (+ 1 2))" >> lexer;
  std::queue<ogol::core::Token> tokens = lexer.tokenize();
  ogol::core::Parser parser(tokens);
  parser.parse().Eval(main_env);
  return 0;
}
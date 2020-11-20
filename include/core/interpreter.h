#pragma once

#include <core/env.h>
#include <core/lexer.h>
#include <core/parser.h>

namespace ogol::core {
static ogol::core::Env main_env(nullptr,
                                map<string, ogol::core::SExpr>{
                                    {"print", Atom(ogol::core::Print)},
                                    {"define", Atom(ogol::core::Define)},
                                    {"+", Atom(ogol::core::Add)},
                                    {"-", Atom(ogol::core::Sub)},
                                    {"*", Atom(ogol::core::Mul)},
                                    {"/", Atom(ogol::core::Div)},
                                });
/**
 * Class which takes in source, constructs a lexer, constructs a parser,
 * and executes it.
 */
class Interpreter {
public:
  /**
   * Overloaded input operator which will load and execute source.
   */
  friend std::istream &operator>>(std::istream &input,
                                  Interpreter &interpreter);
  /**
    Overloaded input operator which passes in source code as a direct string.
   */
  friend string &operator>>(const string &input, Interpreter &interpreter);
  /**
   * Equivalent to << with order flipped.
   */
  friend std::istream &operator<<(Interpreter &interpreter,
                                  std::istream &input);
  /**
   * Equivalent to << with order flipped.
   */
  friend string &operator<<(Interpreter &interpreter,
                                  const string &input);

private:
  /**
   * Helper method which runs source code given a lexer.
   */
  void Run(Lexer lexer);
  SExpr root_;
};

} // namespace ogol::core
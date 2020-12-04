#pragma once

#include <core/env.h>
#include <core/lexer.h>
#include <core/parser.h>

namespace ogol::core {

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
   * Equivalent to << with order flipped.
   */
  friend std::istream &operator<<(Interpreter &interpreter,
                                  std::istream &input);

  /**
   * Helper method which runs source code given a lexer.
   */
  void Run();

private:
  string source_;
};

static Env base_env(nullptr, map<string, ogol::core::SExpr>{
                                 {"print", Atom(ogol::core::Print)},
                                 {"define", Atom(ogol::core::Define)},
                                 {"+", Atom(ogol::core::Add)},
                                 {"-", Atom(ogol::core::Sub)},
                                 {"*", Atom(ogol::core::Mul)},
                                 {"/", Atom(ogol::core::Div)},
                             });
} // namespace ogol::core

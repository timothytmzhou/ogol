#pragma once

#include <core/env.h>
#include <core/lexer.h>
#include <core/parser.h>

using ogol::core::SExpr;

namespace ogol::core {

/**
 * Class which takes in source, constructs a lexer, constructs a parser,
 * and executes it.
 */
class Interpreter {
public:
  /**
   * Constructor which will create an interpreter that will mutate the supplied
   * turtle.
   */
  explicit Interpreter();
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
  void Run(Turtle *turtle);

private:
  string source_;
  Env env_;
};

static const map<string, SExpr> kBuiltIns{
    {"print", Atom(ogol::core::Print)},
    {"define", Atom(ogol::core::Define)},
    {"+", Atom(ogol::core::Add)},
    {"-", Atom(ogol::core::Sub)},
    {"*", Atom(ogol::core::Mul)},
    {"/", Atom(ogol::core::Div)},
    {"forward", Atom(ogol::core::Forward)},
    {"speed", Atom(ogol::core::SetSpeed)},
    {"rotate", Atom(ogol::core::Rotate)},
    {"color", Atom(ogol::core::SetColor)},
};

} // namespace ogol::core

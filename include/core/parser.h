#pragma once

#include "core/s_expr.h"
#include "queue"
#include "token.h"

using std::queue;

namespace ogol::core {

class Parser {
public:
  /**
   * Constructor which takes in a queue of tokens. Should be direct output of
   * lexer.tokenize.
   */
  Parser(queue<Token> &tokens);
  /**
   * Parses the entire program into a single S-expression.
   */
  SExpr parse();

private:
  queue<Token> tokens_;
};

} // namespace ogol::core

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
   * lexer.tokenize().
   */
  explicit Parser(queue<Token> tokens);
  /**
   * Parses the entire program into a single S-expression.
   */
  SExpr parse();

private:
  static Atom ParseToken(const Token &token);
  queue<Token> tokens_;
};

} // namespace ogol::core

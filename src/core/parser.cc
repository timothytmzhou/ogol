#include "core/parser.h"
#include "core/exception.h"

namespace ogol::core {

Parser::Parser(queue<Token> &tokens) : tokens_(tokens) {}

SExpr Parser::parse() {
  vector<SExpr> parsed;
  Token token = tokens_.front();
  tokens_.pop();
  if (token.value != "(") {
    throw ParseError(
        "Attempted to parse start of S-expression, but no such element found.",
        token.line_num);
  }
  while (token.value != ")") {
    if (tokens_.empty()) {
      throw ParseError("Unexpected EOF: unbalanced parenthetical.",
                       token.line_num);
    }
    token = tokens_.front();
    if (token.value == "(") {
      parsed.push_back(parse());
    } else if (token.value != ")"){
      parsed.emplace_back(ParseToken(token));
      tokens_.pop();
    }
  }
  tokens_.pop();
  return SExpr(parsed);
}

Atom Parser::ParseToken(const Token &token) {
  switch(token.token_type) {
  case TokenType::kInteger:
    return Atom(std::stoi(token.value));
  case TokenType::kReal:
    return Atom(std::stod(token.value));
  case TokenType::kString:
    return Atom(token.value);
  default:
    return Atom(token);
  }
}

} // namespace ogol::core
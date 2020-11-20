#include "core/token.h"

#include <utility>

namespace ogol::core {

Token::Token(const TokenType &token_type, string value)
    : token_type(token_type), value(std::move(value)) {}

Token::Token(const TokenType &token_type, string value, size_t line_num)
    : token_type(token_type), value(std::move(value)), line_num(line_num) {}

bool operator==(const Token &a, const Token &b) {
  return a.value == b.value && a.token_type == b.token_type &&
         a.line_num == b.line_num;
}

bool operator!=(const Token &a, const Token &b) { return !(a == b); }

} // namespace ogol::core
#pragma once

#include <string>
using std::string;

namespace ogol::core {

enum class TokenType { kInteger, kReal, kString, kIdentifier, kGrouping };

class Token {
public:
  Token(TokenType token_type, string value)
      : token_type(token_type), value(value) {}
  TokenType token_type;
  string value;
};

/*
 * Equality comparison: two tokens are the same if they have the same value
 * and token type.
 */
bool operator==(const Token &a, const Token &b);
/*
 * Inequality comparison: equivalent to !(a == b).
 */
bool operator!=(const Token &a, const Token &b);
} // namespace ogol::core

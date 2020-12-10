#pragma once

#include <string>
#include <utility>

using std::string;

namespace ogol::core {

/**
 * Enum which serves to separate tokens into various catgories during lexical
 * analysis.
 */
enum class TokenType { kInteger, kReal, kString, kIdentifier, kGrouping };

/**
 * Class which stores a value and a token type.
 */
class Token {
public:
  Token() = default;
  Token(const TokenType &token_type, string value);
  Token(const TokenType &token_type, string value, size_t line_num);
  TokenType token_type;
  string value;
  size_t line_num{};
};

/**
 * Equality comparison: two tokens are the same if they have the same value
 * and token type.
 */
bool operator==(const Token &a, const Token &b);
/**
 * Inequality comparison: equivalent to !(a == b).
 */
bool operator!=(const Token &a, const Token &b);
} // namespace ogol::core

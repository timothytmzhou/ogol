#pragma once

#include "token.h"
#include <map>
#include <queue>
#include <regex>
#include <string>

using std::map;
using std::queue;
using std::regex;
using std::string;

namespace ogol::core {

// tokens are delimited by chains of space-like characters
// these will be skipped during lexical analysis
const string kSeparatorPattern = "\\s+";
// parenthesis act as  grouping elements
const string kGroupingPattern = "[()]";
// integers are strings of digits
const string kIntegerPattern = "[-]?[0-9]+";
// reals are strings of digits with a . in between (first string may be
// empty, e.g '.9'
const string kRealPattern = "[-]?[0-9]*\\.[0-9]+";
// identifiers should be a chain of symbols (+, -, etc.) or a string of
// letters, digits, and underscores not starting with a digit
const string kIdentifierPattern = "[+\\-*/<=>!^|&]+|[a-zA-Z_]\\w*";
// strings can be either single or double quoted
const string kStringPattern = "\".*?\"|'.*?'";

// map between regex patterns and token types
const map<string, TokenType> kTokenPatterns{
    {kIntegerPattern, TokenType::kInteger},
    {kRealPattern, TokenType::kReal},
    {kStringPattern, TokenType::kString},
    {kIdentifierPattern, TokenType::kIdentifier},
    {kGroupingPattern, TokenType::kGrouping}};

/**
 * Loads and tokenizes source code into a parsable form. Overloads the <<
 * operator for both iostream and strings for loading in code. Provides a single
 * public method, tokenize(), which returns a queue of Token objects.
 */
class Lexer {
public:
  /**
   * Performs lexical analysis on source to split it into easily parsed Token
   * objects.
   */
  queue<Token> tokenize();

  /**
   * Overloaded input operator which will load in source code to be lexed.
   */
  friend std::istream &operator>>(std::istream &input, Lexer &lexer);
  /**
    Overloaded input operator which passes in source code as a direct string.
   */
  friend string &operator>>(const string &input, Lexer &lexer);
  /**
   * Equivalent to << with order flipped.
   */
  friend std::istream &operator<<(Lexer &lexer, std::istream &input);
  /**
   * Equivalent to << with order flipped.
   */
  friend string &operator<<(Lexer &lexer, const string &input);

private:
  string source_;
  size_t current_line_ = 1;
  /**
   * Helper method to handle whitespaces. Returns true if whitespace was
   * consumed and the iterator was advanced.
   */
  bool read_whitespaces(string::iterator &it);
  /**
   * Checks if the beginning of the source matches the supplied pattern. Returns
   * an empty string if there is no matching source, otherwise returns the
   * matched token.
   *
   * Note: matches only register if trailing context is properly delimited. For
   * example: '9x' and '\d' will not result produce a match, because one would
   * not want to split '9' and 'x' into separate tokens.
   */
  static string check_pattern(const string &source, const string &pattern);
  /**
   * Handles a token which cannot be identified by the lexer.
   */
  void handle_invalid_token(const string& remaining) const;
};

} // namespace ogol::core

#include <boost/format.hpp>
#include <core/exception.h>
#include <core/lexer.h>
#include <regex>

namespace ogol::core {

queue<Token> ogol::core::Lexer::tokenize() {
  queue<Token> tokens;
  for (auto it = source_.begin(); it != source_.end();) {
    string sub = string(it, source_.end());
    // skip whitespaces
    if (std::regex_search(sub, std::regex("^" + kSeparatorPattern))) {
      ++it;
      continue;
    }
    bool found_match = false;
    // iterate through patterns, checking each one to see if they match
    for (auto const &[pattern, token_type] : kTokenPatterns) {
      string m = check_pattern(sub, pattern);
      if (!m.empty()) {
        it += m.length();
        tokens.emplace(token_type, m);
        found_match = true;
        break;
      }
    }
    if (!found_match) {
      handle_invalid_token(it);
    }
  }
  return tokens;
}

string Lexer::check_pattern(const string &source, const string &pattern) {
  std::smatch m;
  // if the current pattern we are checking is not a grouping character, then
  // either the next token should be a grouping character, or it should be a
  // separator (two non-grouping tokens should always be separated with the
  // separating pattern)
  if (kTokenPatterns.at(pattern) == TokenType::kGrouping) {
    std::regex_search(source, m,
                      regex(boost::str(boost::format("^%s") % pattern)));
    return m[0];
  } else {
    std::regex_search(
        source, m,
        regex(boost::str(boost::format("^(%s)(?:%s|%s|$)") % pattern %
                         kSeparatorPattern % kGroupingPattern)));
    return m[1];
  }
}

void Lexer::handle_invalid_token(string::iterator invalid) {
  // gets line of invalid token
  size_t i = 1;
  auto it = source_.begin();
  for (; it != invalid; ++it) {
    if (*it == '\n') {
      ++i;
    }
  }
  std::smatch m;
  string remaining = string(it, source_.end());
  std::regex_search(remaining, m, regex("^\\w+"));
  throw LexError(
      boost::str(boost::format("Invalid token at line %i: %s") % i % m.str()));
}

std::iostream &operator>>(std::iostream &input, Lexer &lexer) {
  std::stringstream ss;
  ss << input.rdbuf();
  lexer.source_ = ss.str();
  return input;
}
string &operator>>(const string &input, Lexer &lexer) {
  lexer.source_ = input;
  return const_cast<string &>(input);
}
std::iostream &operator<<(Lexer &lexer, std::iostream &input) {
  return input >> lexer;
}
string &operator<<(Lexer &lexer, const string &input) { return input >> lexer; }

} // namespace ogol::core

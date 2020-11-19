#include <boost/format.hpp>
#include <core/exception.h>
#include <core/lexer.h>
#include <regex>

namespace ogol::core {

queue<Token> ogol::core::Lexer::tokenize() {
  queue<Token> tokens;
  for (auto it = source_.begin(); it != source_.end();) {
    string remaining = string(it, source_.end());
    // skip whitespaces
    if (read_whitespaces(it)) {
      continue;
    }
    bool found_match = false;
    // iterate through patterns, checking each one to see if they match
    for (auto const &[pattern, token_type] : kTokenPatterns) {
      string m = check_pattern(remaining, pattern);
      if (!m.empty()) {
        it += m.length();
        tokens.emplace(token_type, m, current_line_);
        found_match = true;
        break;
      }
    }
    if (!found_match) {
      handle_invalid_token(remaining);
    }
  }
  return tokens;
}

bool Lexer::read_whitespaces(string::iterator &it) {
  std::smatch m;
  string sub(it, source_.end());
  if (std::regex_search(sub, m, std::regex("^" + kSeparatorPattern))) {
    // updates current line number based on number of new lines counted
    string separators = m.str();
    it += separators.length();
    current_line_ += std::count(separators.begin(), separators.end(), '\n');
    return true;
  } else {
    return false;
  }
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

void Lexer::handle_invalid_token(const string &remaining) {
  std::smatch invalid_token;
  std::regex_search(remaining, invalid_token, regex("^\\w+"));
  throw LexError(boost::str(boost::format("Invalid token at line %i: %s") %
                            current_line_ % invalid_token.str()));
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

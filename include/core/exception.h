#pragma once

#include <string>
using std::exception;
using std::string;

namespace ogol::core {

/**
 * Custom exception class which displays an error message.
 */
class OgolError : public exception {
public:
  explicit OgolError(string  msg);
  [[nodiscard]] const char *what() const noexcept override;

private:
  string msg_;
};

/**
 * Exceptions which stem from lexical analysis.
 */
class LexError : public OgolError {
  using OgolError::OgolError;
};

} // namespace ogol::core

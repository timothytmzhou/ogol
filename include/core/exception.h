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
  explicit OgolError(string msg);
  explicit OgolError(const string &msg, size_t line_num);
  [[nodiscard]] const char *what() const noexcept override;

private:
  string msg_;
  size_t line_num_{};
};

/**
 * Exceptions which stem from lexical analysis.
 */
class LexError : public OgolError {
  using OgolError::OgolError;
};

/**
 * Exceptions which stem from attempting to access a non-existent name.
 */
class LookupError : public OgolError {
  using OgolError::OgolError;
};

/**
 * Exceptions which stem from failing to parse the input.
 */
class ParseError : public OgolError {
  using OgolError::OgolError;
};

/**
 * Exceptions which stem from illegal argument to procedures.
 */
class ArgumentError : public OgolError {
  using OgolError::OgolError;
};

/**
 * Exceptions which stem from objects of the wrong type being passed.
 */
class TypeError : public OgolError {
  using OgolError::OgolError;
};

/**
 * Exceptions which stem from trying to create an illegal definition.
 */
class DefinitionError : public OgolError {
  using OgolError::OgolError;
};

} // namespace ogol::core

#pragma once

#include <string>
using std::exception;
using std::string;

namespace ogol::core {

class OgolError : public exception {
public:
  explicit OgolError(string msg);
  [[nodiscard]] const char *what() const noexcept override;

private:
  string msg_;
};

class LexError : public OgolError {
  using OgolError::OgolError;
};

} // namespace ogol::core

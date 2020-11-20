#include "core/env.h"
#include "core/exception.h"

#include <utility>

namespace ogol::core {

Env::Env(shared_ptr<Env> parent, map<string, SExpr> names)
    : parent_(std::move(parent)), names_(std::move(names)) {}

SExpr &Env::operator[](const Token &identifier_token) {
  if (names_.find(identifier_token.value) == names_.end()) {
    if (parent_) {
      return (*parent_)[identifier_token];
    } else {
      throw UndefinedNameError("Could not find ", identifier_token.line_num);
    }
  }
  return names_.at(identifier_token.value);
}

} // namespace ogol::core

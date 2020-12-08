#include "core/env.h"
#include "core/exception.h"

#include <utility>

namespace ogol::core {

Env::Env(shared_ptr<Env> parent, map<string, SExpr> names, Turtle *turtle)
    : turtle(*turtle), parent_(std::move(parent)), names_(std::move(names)) {}

SExpr &Env::operator[](const string &name) {
  if (!Contains(name)) {
    // if the supplied name has not been defined in this container, but has
    // been defined in an outer scope, return the value corresponding to that
    // name
    auto parent = parent_;
    while (parent) {
      if (parent->Contains(name)) {
        return parent->names_[name];
      }
      parent = parent->parent_;
    }
  }
  return names_[name];
}

bool Env::Contains(const string &name) {
  return names_.find(name) == names_.end();
}

} // namespace ogol::core

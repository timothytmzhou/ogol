#pragma once

#include <core/procedures.h>
#include <core/s_expr.h>
#include <core/token.h>
#include <map>
#include <memory>
#include <string>

using std::map;
using std::shared_ptr;
using std::string;

namespace ogol::core {

// forward declaration since Env and SExpr rely on each other
class SExpr;
/**
 * Stores an environment, a mapping between names and procedures/S-expressions.
 */
class Env {
public:
  /**
   * Constructor which takes in a pointer to an outer environment and an
   * initial mapping of names to S-Expressions.
   */
  Env(shared_ptr<Env> parent_, map<string, SExpr> names);
  /**
   * Overloaded [] operator -- if the name is not defined in this environment
   * but is defined in an outer environment, returns reference to that
   * environment's names_[name] map element, otherwise return's this one's
   * names_[name] map element.
   */
  SExpr &operator[](const string &name);

private:
  /**
   * Helper method to check if a name is in this environment (only checks inner
   * scope).
   */
  bool Contains(const string &name);
  shared_ptr<Env> parent_;
  map<string, SExpr> names_;
};

} // namespace ogol::core

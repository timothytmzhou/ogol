#pragma once

#include <core/s_expr.h>
#include <core/token.h>
#include <map>
#include <memory>
#include <string>

using std::string;
using std::shared_ptr;
using std::map;

namespace ogol::core {

// forward declaration since Env and SExpr rely on each other
class SExpr;
/**
 * Stores an environment, a mapping between names and procedures/S-expressions.
 */
class Env {
public:
  Env(shared_ptr<Env> parent_, map<string, SExpr> names);
  SExpr & operator[] (const Token& identifier_token);
private:
  shared_ptr<Env> parent_;
  map<string, SExpr> names_;
};

} // namespace ogol::core

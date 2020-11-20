#pragma once

#include <core/s_expr.h>
#include <core/token.h>
#include <map>
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using std::map;

namespace ogol::core {

class SExpr;
/**
 * Stores an environment, a mapping between names and procedures/S-expressions.
 */
class Env {
public:
  Env(unique_ptr<Env> parent_, map<string, SExpr> names);
  SExpr & operator[] (const Token& identifier_token);
private:
  unique_ptr<Env> parent_;
  map<string, SExpr> names_;
};

} // namespace ogol::core

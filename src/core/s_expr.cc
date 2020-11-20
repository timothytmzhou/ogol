#include "core/s_expr.h"

#include <utility>

namespace ogol::core {

Atom::Atom(Token token) : token(std::move(token)) {}
Atom::Atom(Proc proc) : proc(proc) {}

bool SExpr::IsAtomic() { return s_exprs_.size() == 1; }

bool SExpr::IsNil() { return !IsAtomic() && s_exprs_.empty(); }

SExpr SExpr::GetLeft() { return s_exprs_[0]; }

SExpr SExpr::GetRight() {
  std::vector<SExpr> right = s_exprs_;
  right.erase(right.begin());
  return SExpr(right);
}

SExpr SExpr::Eval(Env env) {
  // TODO: write this
}

SExpr::SExpr(Atom atom) : atom_(atom){}

SExpr::SExpr(vector<SExpr> s_exprs) : s_exprs_(s_exprs) {}

SExpr::SExpr(vector<Atom> atoms) {
  for (const Atom& atom : atoms) {
    s_exprs_.emplace_back(atom);
  }
}

Atom SExpr::AsAtom() {
  if (IsAtomic()) {
    return atom_;
  } else {
    // TODO: throw exception here
  }
}
} // namespace ogol::core

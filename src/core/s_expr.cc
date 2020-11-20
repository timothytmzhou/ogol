#include "core/s_expr.h"

#include <utility>

namespace ogol::core {

Atom::Atom(Token token) : token(std::move(token)) {}

Atom::Atom(Proc proc) : proc(proc) {}

Atom::Atom(double val) : token(Token(TokenType::kReal, std::to_string(val))) {}

Atom::Atom(int val) : token(Token(TokenType::kInteger, std::to_string(val))) {}

Atom::Atom(string val) : token(Token(TokenType::kString, std::move(val))) {}

Atom::operator SExpr() const { return SExpr(*this); }

bool SExpr::IsAtomic() const { return is_atomic_; }

bool SExpr::IsNil() const { return !IsAtomic() && s_exprs_.empty(); }

SExpr SExpr::GetLeft() const { return s_exprs_[0]; }

SExpr SExpr::GetRight() const {
  std::vector<SExpr> right = s_exprs_;
  right.erase(right.begin());
  return SExpr(right);
}

SExpr SExpr::Eval(Env &env) const {
  return SExpr(Atom());
  // TODO: write this
}

SExpr::SExpr() : is_atomic_(false) {}

SExpr::SExpr(Atom atom) : atom_(std::move(atom)), is_atomic_(true) {}

SExpr::SExpr(vector<SExpr> s_exprs)
    : s_exprs_(std::move(s_exprs)), is_atomic_(false) {}

SExpr::SExpr(const vector<Atom> &atoms) : is_atomic_(false) {
  for (const Atom &atom : atoms) {
    s_exprs_.emplace_back(atom);
  }
}

Atom SExpr::AsAtom() const {
  if (IsAtomic()) {
    return atom_;
  } else {
    throw std::invalid_argument("a");
    // TODO: throw exception here
  }
}

string SExpr::str() {
  if (IsNil()) {
    return "nil";
  } else if (IsAtomic()) {
    if (atom_.proc) {
      return "<proc>";
    } else {
      return atom_.token.value;
    }
  } else {
    string rep = "(";
    for (auto &s_expr : s_exprs_) {
      rep += s_expr.str() + " ";
    }
    rep.pop_back();
    rep += ")";
    return rep;
  }
}

} // namespace ogol::core

#include "core/s_expr.h"
#include "core/exception.h"

#include <utility>

namespace ogol::core {

Atom::Atom(Token token) : token(std::move(token)) {
  if (token.token_type == TokenType::kInteger) {
    int_value = std::stoi(token.value);
  } else if (token.token_type == TokenType::kReal) {
    real_value = std::stod(token.value);
  } else if (token.token_type == TokenType::kString) {
    string_value = token.value;
  }
}

Atom::Atom(Proc proc) : proc(proc) {}

Atom::Atom(double val)
    : token(Token(TokenType::kReal, std::to_string(val))), real_value(val) {}

Atom::Atom(int val)
    : token(Token(TokenType::kInteger, std::to_string(val))), int_value(val) {}

Atom::Atom(string val)
    : token(Token(TokenType::kString, std::move(val))), string_value(val) {}

Atom::operator SExpr() const { return SExpr(*this); }

bool SExpr::IsAtomic() const { return is_atomic_; }

bool SExpr::IsNil() const { return !IsAtomic() && s_exprs_.empty(); }

SExpr SExpr::GetLeft() const {
  if (IsAtomic()) {
    throw TypeError("Attempted to split an atomic S-expression.");
  } else if (IsNil()) {
    return SExpr();
  } else {
    return s_exprs_[0];
  }
}

SExpr SExpr::GetRight() const {
  if (IsAtomic()) {
    throw TypeError("Attempted to split an atomic S-expression.");
  } else if (IsNil()) {
    return SExpr();
  } else {
    std::vector<SExpr> right = s_exprs_;
    right.erase(right.begin());
    return SExpr(right);
  }
}

SExpr SExpr::Eval(Env* env) const {
  // if the S-expression is nil, return nil
  if (IsNil()) {
    return SExpr();
    // if it is an atom, returns its value
  } else if (IsAtomic()) {
    Token self = AsAtom().token;
    if (self.token_type == TokenType::kIdentifier) {
      return (*env)[self.value];
    } else {
      return *this;
    }
    // otherwise check if it is a function call
  } else if (GetLeft().IsAtomic() &&
             GetLeft().AsAtom().token.token_type == TokenType::kIdentifier) {
    SExpr proc = GetLeft().Eval(env);
    if (proc.IsAtomic() && proc.AsAtom().proc) {
      return proc.AsAtom().proc(GetRight(), env);
    } else {
      throw TypeError(proc.str() + " is not callable.");
    }
    // otherwise evaluate all individual elements of the S-expression
  } else {
    vector<SExpr> s_exprs;
    for (const SExpr &s_expr : s_exprs_) {
      s_exprs.push_back(s_expr.Eval(env));
    }
    return SExpr(s_exprs);
  }
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
    throw TypeError("Attempted to convert non-atomic S-expression to atom.");
  }
}

vector<Atom> SExpr::Unpack() const {
  vector<Atom> atoms;
  for (const SExpr &s_expr : s_exprs_) {
    atoms.push_back(s_expr.AsAtom());
  }
  return atoms;
}

string SExpr::str() const {
  if (IsNil()) {
    return "nil";
  } else if (IsAtomic()) {
    if (atom_.proc) {
      return "<proc>";
    } else {
      auto token = atom_.token;
      if (token.token_type == TokenType::kString) {
        // format string
        return "\"" + token.value + "\"";
      } else {
        return token.value;
      }
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

size_t SExpr::size() const {
  if (IsAtomic()) {
    return 1;
  } else if (IsNil()) {
    return 0;
  } else {
    return s_exprs_.size();
  }
}

} // namespace ogol::core

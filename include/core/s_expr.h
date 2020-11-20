#pragma once

#include <core/env.h>
#include <core/token.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace ogol::core {

class SExpr;
class Env;
// type alias for a procedure (all procedures are SExpr -> SExpr)
typedef SExpr (*Proc)(SExpr &);

/**
 * An atom, which wraps a single value. Practically, since we are constrained
 * by c++'s type system, we define two fields: proc and token. Atomic procedures
 * should only use proc, and atomic tokens should only use token.
 */
struct Atom {
  Atom() = default;
  Atom(Token token);
  Atom(Proc proc);
  Token token;
  Proc proc = nullptr;
};

/**
 * AS-expression is recursively defined as either an atom, or
 * of form (S1 . S2), where S1 and S2 are both S-expressions, but here we just
 * use a vector of SExprs for convenience, and define GetLeft and GetRight to
 * emulate the recursive structure.
 */
class SExpr {
public:
  /**
   * Constructs an atomic S-expression.
   */
  explicit SExpr(Atom atom);
  /**
   * Constructs a S-expression from a vector of S-expressions.
   */
   explicit SExpr(vector<SExpr> s_exprs);
  /**
   * Constructs an S-expression from a vector of atoms. Equivalent to wrapping
   * each atom in an atomic SExpr and calling SExpr(vector<SExpr>).
   */
  explicit SExpr(const vector<Atom>& atoms);
  /**
   * Returns a boolean with whether or not this SExpr is nil (atoms_ is length
   * 0).
   */
  bool IsNil();
  /**
   * Returns a boolean with whether or not this SExpr is an atom (atoms_ is
   * length 1).
   */
  bool IsAtomic() const;
  /**
   * Returns atom if the S-expression is atomic, otherwise throws error.
   */
  Atom AsAtom();
  /**
   * Gets the left S-expression (first element in vector).
   */
  SExpr GetLeft();
  /**
   * Gets the right S-expression (every element in the vector except the first,
   * passed into the constructor for a new SExpr).
   */
  SExpr GetRight();
  /**
   * Evaluates the S-expression. If it is of form (func x y), evaluates itself
   * and returns the resulting S-expression. Otherwise, returns itself.
   */
  SExpr Eval(Env env);
  /**
   * Gets string representation of S-expression.
   */
  string str();

private:
  Atom atom_;
  vector<SExpr> s_exprs_;
  bool is_atomic_;
};

} // namespace ogol::core

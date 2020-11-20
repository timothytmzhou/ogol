#pragma once

#include <core/env.h>
#include <core/token.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace ogol::core {

// forward declarations since structures rely on each other
class SExpr;
class Env;
// type alias for a procedure (all procedures are SExpr -> SExpr)
typedef SExpr (*Proc)(const SExpr &, Env &);

/**
 * An atom, which wraps a single value. Practically, since we are constrained
 * by c++'s type system, we define two fields: proc and token. Atomic procedures
 * should only use proc, and atomic tokens should only use token.
 */
struct Atom {
  Atom() = default;
  /*
   * Constructor for an Atom from a supplied double value.
   */
  explicit Atom(double val);
  /*
   * Constructor for an Atom from a supplied integer value.
   */
  explicit Atom(int val);
  /*
   * Constructor for an Atom from a supplied string value.
   */
  explicit Atom(string val);
  /**
   * Constructor for an Atom from a supplied token.
   */
  explicit Atom(Token token);
  /**
   * Constructor for an Atom from a supplied procedure.
   */
  explicit Atom(Proc proc);
  /**
   * Allows for cast to SExpr (just calls the SExpr atomic constructor).
   */
  explicit operator SExpr();

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
   * Constructs a nil SExpr.
   */
  SExpr();
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
  explicit SExpr(const vector<Atom> &atoms);
  /**
   * Returns a boolean with whether or not this SExpr is nil (atoms_ is length
   * 0).
   */
  [[nodiscard]] bool IsNil() const;
  /**
   * Returns a boolean with whether or not this SExpr is an atom (atoms_ is
   * length 1).
   */
  [[nodiscard]] bool IsAtomic() const;
  /**
   * Returns atom if the S-expression is atomic, otherwise throws error.
   */
  [[nodiscard]] Atom AsAtom() const;
  /**
   * Gets the left S-expression (first element in vector).
   */
  [[nodiscard]] SExpr GetLeft() const;
  /**
   * Gets the right S-expression (every element in the vector except the first,
   * passed into the constructor for a new SExpr).
   */
  [[nodiscard]] SExpr GetRight() const;
  /**
   * Evaluates the S-expression. If it is of form (func x y), evaluates itself
   * and returns the resulting S-expression. Otherwise, returns itself.
   */
  [[nodiscard]] SExpr Eval(Env &env) const;
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

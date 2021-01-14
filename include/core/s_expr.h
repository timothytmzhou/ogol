#pragma once

#include <core/env.h>
#include <core/token.h>
#include <string>
#include <vector>

#include <visualizer/turtle.h>

using std::string;
using std::vector;

using ogol::visualizer::Turtle;

namespace ogol::core {

// forward declarations since structures rely on each other
class SExpr;
class Env;
// type alias for a procedure (all procedures are SExpr -> SExpr)
typedef SExpr (*Proc)(const SExpr &, Env *, Turtle *turtle);

/**
 * An atom, which wraps a single value. Practically, since we are constrained
 * by c++'s type system, we define two fields: proc and token. Atomic procedures
 * should only use proc, and atomic tokens should only use token.
 */
struct Atom {
  Atom() = default;
  /**
   * Constructor for an Atom from a supplied token.
   */
  explicit Atom(Token token);
  /**
   * Constructor for an Atom from a supplied procedure.
   */
  explicit Atom(Proc proc);
  /**
   * Constructor for an Atom from a supplied double value.
   */
  explicit Atom(double val);
  /**
   * Constructor for an Atom from a supplied integer value.
   */
  explicit Atom(int val);
  /**
   * Constructor for an Atom from a supplied string value.
   */
  explicit Atom(const string &val);
  operator SExpr() const;
  Token token;
  int int_value;
  double real_value;
  string string_value;
  Proc proc = nullptr;
};

/**
 * A S-expression is recursively defined as either an atom, or
 * of form (S1 . S2), where S1 and S2 are both S-expressions, but here we just
 * use a vector of SExprs for convenience, and define GetHead and GetTail to
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
   * Unpacks the S-expression into a vector of atoms.
   */
  [[nodiscard]] vector<Atom> Unpack() const;
  /**
   * Gets the head S-expression (first element in vector).
   */
  [[nodiscard]] SExpr GetHead() const;
  /**
   * Gets the right S-expression (every element in the vector except the first,
   * passed into the constructor for a new SExpr).
   */
  [[nodiscard]] SExpr GetTail() const;
  /**
   * Evaluates the S-expression. If it is of form (func x y), evaluates itself
   * and returns the resulting S-expression. Otherwise, returns itself.
   */
  SExpr Eval(Env *env, Turtle *turtle) const;
  /**
   * Gets string representation of S-expression.
   */
  [[nodiscard]] string str() const;
  /**
   * Gets number of elements stored (1 if atomic)
   */
  [[nodiscard]] size_t size() const;

private:
  Atom atom_;
  vector<SExpr> s_exprs_;
  bool is_atomic_;
};

} // namespace ogol::core

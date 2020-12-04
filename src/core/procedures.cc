#include "core/procedures.h"
#include "core/exception.h"
#include "core/s_expr.h"
#include <iostream>

namespace ogol::core {

SExpr Print(const SExpr &args, Env &env) {
  if (args.size() == 1) {
    std::cout << args.GetLeft().Eval(env).str() << "\n";
  } else {
    throw ArgumentError("print expects one argument.");
  }
  return SExpr();
}

SExpr Define(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft();
  SExpr right = args.GetRight();
  if (right.size() != 1) {
    throw DefinitionError("Must assign one value to a name.");
  }
  right = right.GetLeft().Eval(env);
  if (!left.IsAtomic() &&
      left.AsAtom().token.token_type == TokenType::kIdentifier) {
    throw DefinitionError("Cannot define value for a non-identifier.");
  }
  env[left.AsAtom().token.value] = right;
  return SExpr();
}

SExpr Add(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot add non-atomic value.");
  } else {
    TokenType left_token_type = left.AsAtom().token.token_type;
    if (left_token_type == TokenType::kReal ||
        left_token_type == TokenType::kInteger) {
      // TODO: Arithmetic always produces reals
      double remaining =
          (right.IsNil()) ? 0 : stod(Add(right, env).AsAtom().token.value);
      return Atom(stod(left.AsAtom().token.value) + remaining);
    } else {
      throw TypeError("Unexpected type passed to add.");
    }
  }
}

SExpr Sub(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot add non-atomic value.");
  } else {
    TokenType left_token_type = left.AsAtom().token.token_type;
    if (left_token_type == TokenType::kReal ||
        left_token_type == TokenType::kInteger) {
      // TODO: Arithmetic always produces reals
      double remaining =
          (right.IsNil()) ? 0 : stod(Add(right, env).AsAtom().token.value);
      return Atom(stod(left.AsAtom().token.value) - remaining);
    } else {
      throw TypeError("Unexpected type passed to add.");
    }
  }
}

SExpr Mul(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot add non-atomic value.");
  } else {
    TokenType left_token_type = left.AsAtom().token.token_type;
    if (left_token_type == TokenType::kReal ||
        left_token_type == TokenType::kInteger) {
      // TODO: Arithmetic always produces reals
      double remaining =
          (right.IsNil()) ? 1 : stod(Mul(right, env).AsAtom().token.value);
      return Atom(stod(left.AsAtom().token.value) * remaining);
    } else {
      throw TypeError("Unexpected type passed to add.");
    }
  }
}

SExpr Div(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot add non-atomic value.");
  } else {
    TokenType left_token_type = left.AsAtom().token.token_type;
    if (left_token_type == TokenType::kReal ||
        left_token_type == TokenType::kInteger) {
      // TODO: Arithmetic always produces reals
      double remaining =
          (right.IsNil()) ? 1 : stod(Mul(right, env).AsAtom().token.value);
      return Atom(stod(left.AsAtom().token.value) / remaining);
    } else {
      throw TypeError("Unexpected type passed to add.");
    }
  }
}

} // namespace ogol::core
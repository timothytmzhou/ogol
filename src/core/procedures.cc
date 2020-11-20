#include "core/procedures.h"
#include "core/exception.h"
#include "core/s_expr.h"
#include <iostream>

namespace ogol::core {

SExpr Print(const SExpr &args, Env &env) {
  if (args.size() == 1) {
    std::cout << args.GetLeft().Eval(env).str();
  } else{
    throw ArgumentError("print expects one argument.");
  }
  return SExpr();
}

SExpr Define(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight().Eval(env);
  if (!left.IsAtomic() &&
      left.AsAtom().token.token_type == TokenType::kIdentifier) {
    throw DefinitionError("Cannot define value for a non-identifier.");
  }
  env[left.AsAtom().token] = right;
  return SExpr();
}

SExpr Add(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot add non-atomic value.");
  } else {
    Token left_token = left.AsAtom().token;
    if (left_token.token_type == TokenType::kInteger) {
      return Atom(stoi(left_token.value) +
                  stoi(Add(right, env).AsAtom().token.value));
    } else if (left_token.token_type == TokenType::kReal) {
      return Atom(stod(left_token.value) +
                  stod(Add(right, env).AsAtom().token.value));
    } else {
      throw TypeError("Unexpected type passed to add.");
    }
  }
}

SExpr Sub(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot subtract from non-atomic value.");
  } else {
    Token left_token = left.AsAtom().token;
    if (left_token.token_type == TokenType::kInteger) {
      return Atom(stoi(left_token.value) -
                  stoi(Add(right, env).AsAtom().token.value));
    } else if (left_token.token_type == TokenType::kReal) {
      return Atom(stod(left_token.value) -
                  stod(Add(right, env).AsAtom().token.value));
    } else {
      throw TypeError("Unexpected type passed to sub.");
    }
  }
}

SExpr Mul(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot multiply non-atomic value.");
  } else {
    Token left_token = left.AsAtom().token;
    if (left_token.token_type == TokenType::kInteger) {
      return Atom(stoi(left_token.value) *
                  stoi(Mul(right, env).AsAtom().token.value));
    } else if (left_token.token_type == TokenType::kReal) {
      return Atom(stod(left_token.value) *
                  stod(Mul(right, env).AsAtom().token.value));
    } else {
      throw TypeError("Unexpected type passed to mul.");
    }
  }
}

SExpr Div(const SExpr &args, Env &env) {
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  if (!left.IsAtomic()) {
    throw ArgumentError("Cannot divide from non-atomic value.");
  } else {
    Token left_token = left.AsAtom().token;
    if (left_token.token_type == TokenType::kInteger) {
      return Atom(stoi(left_token.value) /
                  stoi(Mul(right, env).AsAtom().token.value));
    } else if (left_token.token_type == TokenType::kReal) {
      return Atom(stod(left_token.value) /
                  stod(Mul(right, env).AsAtom().token.value));
    } else {
      throw TypeError("Unexpected type passed to div.");
    }
  }
}

} // namespace ogol::core
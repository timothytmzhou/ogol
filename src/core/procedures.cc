#include "core/procedures.h"
#include "core/exception.h"
#include "core/s_expr.h"
#include <functional>
#include <iostream>

namespace ogol::core {

SExpr Print(const SExpr &args, Env* env) {
  if (args.size() == 1) {
    std::cout << args.GetLeft().Eval(env).str() << "\n";
  } else {
    throw ArgumentError("print expects one argument.");
  }
  return SExpr();
}

SExpr Define(const SExpr &args, Env* env) {
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
  (*env)[left.AsAtom().token.value] = right;
  return SExpr();
}

void CheckNumeric(const SExpr &args) {
  vector<Atom> atoms;
  if (args.IsNil()) {
    throw ArgumentError("Expected sequence of numeric atoms, not " +
                        args.str());
  }
  atoms = args.Unpack();
  if (!std::all_of(atoms.begin(), atoms.end(), [](auto atom) {
        TokenType type = atom.token.token_type;
        return type == TokenType::kInteger || type == TokenType::kReal;
      })) {
    throw TypeError("Received non-numeric type where one was expected.");
  }
}

SExpr Add(const SExpr &args, Env* env) {
  CheckNumeric(args);
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  Atom right_val = right.IsNil() ? Atom(0) : Add(right, env).AsAtom();
  TokenType left_type = left.AsAtom().token.token_type;
  TokenType right_type = right_val.token.token_type;
  if (left_type == TokenType::kInteger && right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().int_value + right_val.int_value);
  } else if (left_type == TokenType::kInteger &&
             right_type == TokenType::kReal) {
    return Atom(left.AsAtom().int_value + right_val.real_value);
  } else if (left_type == TokenType::kReal &&
             right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().real_value + right_val.int_value);
  } else {
    return Atom(left.AsAtom().real_value + right_val.real_value);
  }
}

SExpr Sub(const SExpr &args, Env* env) {
  CheckNumeric(args);
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  Atom right_val = right.IsNil() ? Atom(0) : Add(right, env).AsAtom();
  TokenType left_type = left.AsAtom().token.token_type;
  TokenType right_type = right_val.token.token_type;
  if (left_type == TokenType::kInteger && right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().int_value - right_val.int_value);
  } else if (left_type == TokenType::kInteger &&
             right_type == TokenType::kReal) {
    return Atom(left.AsAtom().int_value - right_val.real_value);
  } else if (left_type == TokenType::kReal &&
             right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().real_value - right_val.int_value);
  } else {
    return Atom(left.AsAtom().real_value - right_val.real_value);
  }
}

SExpr Mul(const SExpr &args, Env* env) {
  CheckNumeric(args);
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  Atom right_val = right.IsNil() ? Atom(1) : Mul(right, env).AsAtom();
  TokenType left_type = left.AsAtom().token.token_type;
  TokenType right_type = right_val.token.token_type;
  if (left_type == TokenType::kInteger && right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().int_value * right_val.int_value);
  } else if (left_type == TokenType::kInteger &&
             right_type == TokenType::kReal) {
    return Atom(left.AsAtom().int_value * right_val.real_value);
  } else if (left_type == TokenType::kReal &&
             right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().real_value * right_val.int_value);
  } else {
    return Atom(left.AsAtom().real_value * right_val.real_value);
  }
}

SExpr Div(const SExpr &args, Env* env) {
  CheckNumeric(args);
  SExpr left = args.GetLeft().Eval(env);
  SExpr right = args.GetRight();
  Atom right_val = right.IsNil() ? Atom(1) : Mul(right, env).AsAtom();
  TokenType left_type = left.AsAtom().token.token_type;
  TokenType right_type = right_val.token.token_type;
  if (left_type == TokenType::kInteger && right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().int_value / right_val.int_value);
  } else if (left_type == TokenType::kInteger &&
             right_type == TokenType::kReal) {
    return Atom(left.AsAtom().int_value / right_val.real_value);
  } else if (left_type == TokenType::kReal &&
             right_type == TokenType::kInteger) {
    return Atom(left.AsAtom().real_value / right_val.int_value);
  } else {
    return Atom(left.AsAtom().real_value / right_val.real_value);
  }
}

} // namespace ogol::core
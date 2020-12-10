#include "core/procedures.h"
#include "core/exception.h"
#include "core/s_expr.h"
#include <functional>
#include <iostream>

namespace ogol::core {

SExpr Print(const SExpr &args, Env *env, Turtle *turtle) {
  if (args.size() == 1) {
    std::cout << args.GetHead().Eval(env, turtle).str() << "\n";
  } else {
    throw ArgumentError("print expects one argument.");
  }
  return SExpr();
}

SExpr Define(const SExpr &args, Env *env, Turtle *turtle) {
  SExpr head = args.GetHead();
  SExpr tail = args.GetTail();
  if (tail.size() != 1) {
    throw DefinitionError("Must assign one value to a name.");
  }
  tail = tail.GetHead().Eval(env, turtle);
  if (!head.IsAtomic() &&
      head.AsAtom().token.token_type == TokenType::kIdentifier) {
    throw DefinitionError("Cannot define value for a non-identifier.");
  }
  (*env)[head.AsAtom().token.value] = tail;
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

SExpr Add(const SExpr &args, Env *env, Turtle *turtle) {
  CheckNumeric(args);
  SExpr head = args.GetHead().Eval(env, turtle);
  SExpr tail = args.GetTail();
  Atom tail_val = tail.IsNil() ? Atom(0) : Add(tail, env, turtle).AsAtom();
  TokenType head_type = head.AsAtom().token.token_type;
  TokenType tail_type = tail_val.token.token_type;
  if (head_type == TokenType::kInteger && tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().int_value + tail_val.int_value);
  } else if (head_type == TokenType::kInteger &&
             tail_type == TokenType::kReal) {
    return Atom(head.AsAtom().int_value + tail_val.real_value);
  } else if (head_type == TokenType::kReal &&
             tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().real_value + tail_val.int_value);
  } else {
    return Atom(head.AsAtom().real_value + tail_val.real_value);
  }
}

SExpr Sub(const SExpr &args, Env *env, Turtle *turtle) {
  CheckNumeric(args);
  SExpr head = args.GetHead().Eval(env, turtle);
  SExpr tail = args.GetTail();
  Atom tail_val = tail.IsNil() ? Atom(0) : Add(tail, env, turtle).AsAtom();
  TokenType head_type = head.AsAtom().token.token_type;
  TokenType tail_type = tail_val.token.token_type;
  if (head_type == TokenType::kInteger && tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().int_value - tail_val.int_value);
  } else if (head_type == TokenType::kInteger &&
             tail_type == TokenType::kReal) {
    return Atom(head.AsAtom().int_value - tail_val.real_value);
  } else if (head_type == TokenType::kReal &&
             tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().real_value - tail_val.int_value);
  } else {
    return Atom(head.AsAtom().real_value - tail_val.real_value);
  }
}

SExpr Mul(const SExpr &args, Env *env, Turtle *turtle) {
  CheckNumeric(args);
  SExpr head = args.GetHead().Eval(env, turtle);
  SExpr tail = args.GetTail();
  Atom tail_val = tail.IsNil() ? Atom(1) : Mul(tail, env, turtle).AsAtom();
  TokenType head_type = head.AsAtom().token.token_type;
  TokenType tail_type = tail_val.token.token_type;
  if (head_type == TokenType::kInteger && tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().int_value * tail_val.int_value);
  } else if (head_type == TokenType::kInteger &&
             tail_type == TokenType::kReal) {
    return Atom(head.AsAtom().int_value * tail_val.real_value);
  } else if (head_type == TokenType::kReal &&
             tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().real_value * tail_val.int_value);
  } else {
    return Atom(head.AsAtom().real_value * tail_val.real_value);
  }
}

SExpr Div(const SExpr &args, Env *env, Turtle *turtle) {
  CheckNumeric(args);
  SExpr head = args.GetHead().Eval(env, turtle);
  SExpr tail = args.GetTail();
  Atom tail_val = tail.IsNil() ? Atom(1) : Mul(tail, env, turtle).AsAtom();
  TokenType head_type = head.AsAtom().token.token_type;
  TokenType tail_type = tail_val.token.token_type;
  if (head_type == TokenType::kInteger && tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().int_value / tail_val.int_value);
  } else if (head_type == TokenType::kInteger &&
             tail_type == TokenType::kReal) {
    return Atom(head.AsAtom().int_value / tail_val.real_value);
  } else if (head_type == TokenType::kReal &&
             tail_type == TokenType::kInteger) {
    return Atom(head.AsAtom().real_value / tail_val.int_value);
  } else {
    return Atom(head.AsAtom().real_value / tail_val.real_value);
  }
}

SExpr Rotate(const SExpr &args, Env *env, Turtle *turtle) {
  if (args.size() == 1) {
    CheckNumeric(args);
    Atom head = args.GetHead().Eval(env, turtle).AsAtom();
    if (head.token.token_type == TokenType::kInteger) {
      turtle->Rotate(head.int_value);
    } else {
      turtle->Rotate(head.real_value);
    }
  } else {
    throw ArgumentError("rotate expects one argument.");
  }
  return SExpr();
}

SExpr SetSpeed(const SExpr &args, Env *env, Turtle *turtle) {
  if (args.size() == 1) {
    CheckNumeric(args);
    Atom head = args.GetHead().Eval(env, turtle).AsAtom();
    if (head.token.token_type == TokenType::kInteger) {
      turtle->SetSpeed(head.int_value);
    } else {
     turtle->SetSpeed(head.real_value);
    }
  } else {
    throw ArgumentError("speed expects one argument.");
  }
  return SExpr();
}

} // namespace ogol::core
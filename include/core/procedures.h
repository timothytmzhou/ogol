#pragma once

#include "core/s_expr.h"

namespace ogol::core {
// forward declarations for needed structures
class SExpr;
class Env;
struct Atom;
/**
 * Prints out a string to the console.
 */
SExpr Print(const SExpr &args, Env &env);
/**
 * Adds a name and value pair to the environment.
 */
SExpr Define(const SExpr &args, Env &env);
/**
 * Adds a list of numbers together.
 */
SExpr Add(const SExpr &args, Env &env);
/**
 * Subtracts the remaining numbers in a list from the first.
 */
SExpr Sub(const SExpr &args, Env &env);
/**
 * Computes the product of a list of numbers.
 */
SExpr Mul(const SExpr &args, Env &env);
/**
 * Divides the first number in a list by the product of the rest.
 */
SExpr Div(const SExpr &args, Env &env);
} // namespace ogol::core
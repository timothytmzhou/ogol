#pragma once

#include <cinder/gl/gl.h>

#include <core/s_expr.h>
#include <visualizer/turtle.h>

using ogol::visualizer::Turtle;

namespace ogol::core {
// forward declarations for needed structures
class SExpr;
class Env;
struct Atom;
/**
 * Prints out a string to the console.
 */
SExpr Print(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Adds a name and value pair to the environment.
 */
SExpr Define(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Checks if args are all numbers (throws exception if not).
 */
void CheckNumeric(const SExpr &args);
/**
 * Adds a list of numbers together.
 */
SExpr Add(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Subtracts the remaining numbers in a list from the first.
 */
SExpr Sub(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Computes the product of a list of numbers.
 */
SExpr Mul(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Divides the first number in a list by the product of the rest.
 */
SExpr Div(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Rotates the turtle.
 */
SExpr Rotate(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Moves the turtle forward.
 */
SExpr Forward(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Changes the speed of the turtle.
 */
SExpr SetSpeed(const SExpr &args, Env *env, Turtle *turtle);
/**
 * Changes the color of the turtle.
 */
SExpr SetColor(const SExpr &args, Env *env, Turtle *turtle);
} // namespace ogol::core
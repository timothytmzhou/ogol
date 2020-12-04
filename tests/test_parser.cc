#include <catch2/catch.hpp>
#include <core/exception.h>
#include <core/lexer.h>
#include <core/parser.h>
#include <vector>

using ogol::core::Atom;
using ogol::core::Lexer;
using ogol::core::ParseError;
using ogol::core::Parser;
using ogol::core::SExpr;

TEST_CASE("Program is not an accepted S-expression form") {
  Lexer lexer;
  "print 1" >> lexer; // this should be '(print 1)'--all programs should be a
                      // list form S-expression
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  REQUIRE_THROWS_AS(parser.parse(), ParseError);
}

TEST_CASE("Unbalanced parenthetical") {
  Lexer lexer;
  "(print 1 ()" >> lexer;
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  REQUIRE_THROWS_AS(parser.parse(), ParseError);
}

TEST_CASE("Nested S-expressions") {
  Lexer lexer;
  "((print 1) (print 2))" >> lexer;
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  REQUIRE(parser.parse().str() == "((print 1) (print 2))");
}

TEST_CASE("Atoms are parsed correctly") {
  Lexer lexer;
  "(1 1.0 'a')" >> lexer;
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  REQUIRE(parser.parse().str() == "(1 1.0 'a')");
}
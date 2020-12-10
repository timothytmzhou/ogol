#include <catch2/catch.hpp>
#include <core/exception.h>
#include <core/interpreter.h>
#include <core/lexer.h>
#include <core/parser.h>

using ogol::core::ArgumentError;
using ogol::core::Env;
using ogol::core::kBuiltIns;
using ogol::core::Lexer;
using ogol::core::Parser;
using ogol::core::TypeError;

Env base_env(nullptr, kBuiltIns);
Turtle base_turtle;

TEST_CASE("Addition") {
  SECTION("No arguments") {
    Lexer lexer("(+)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle),
                      ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(+ 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).str() == "1");
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(+ 1 2 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().int_value ==
            Approx(6));
  }
  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(+ 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().real_value ==
            Approx(3.0));
  }
  SECTION("Arguments of illegal type") {
    Lexer lexer("(+ 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle), TypeError);
  }
}

TEST_CASE("Subtraction") {
  SECTION("No arguments") {
    Lexer lexer("(-)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle),
                      ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(- 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().int_value ==
            1);
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(- 1 2 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().int_value ==
            -4);
  }
  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(- 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().real_value ==
            -1.0);
  }
  SECTION("Arguments of illegal type") {
    Lexer lexer("(+ 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle), TypeError);
  }
}

TEST_CASE("Multiplication") {
  SECTION("No arguments") {
    Lexer lexer("(*)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle),
                      ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(* 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().int_value ==
            1);
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(* 1 2 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().int_value ==
            6);
  }
  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(* 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().real_value ==
            Approx(2.0));
  }
  SECTION("Arguments of illegal type") {
    Lexer lexer("(* 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle), TypeError);
  }
}

TEST_CASE("Division") {
  SECTION("No arguments") {
    Lexer lexer("(/)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle),
                      ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(/ 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().int_value ==
            1);
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(/ 3 1 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).str() == "1");
  }

  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(/ 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(&base_env, &base_turtle).AsAtom().real_value ==
            Approx(.5));
  }

  SECTION("Arguments of illegal type") {
    Lexer lexer("(/ 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(&base_env, &base_turtle), TypeError);
  }
}

TEST_CASE("Defined identifier lookup") {
  Lexer lexer("((define x 3) x)");
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  auto val = parser.parse().Eval(&base_env, &base_turtle);
  REQUIRE(val.GetHead().IsNil());
  REQUIRE(val.GetTail().GetHead().AsAtom().int_value == 3);
}
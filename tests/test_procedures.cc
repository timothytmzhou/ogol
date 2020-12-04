#include <catch2/catch.hpp>
#include <core/exception.h>
#include <core/interpreter.h>
#include <core/lexer.h>
#include <core/parser.h>

using ogol::core::ArgumentError;
using ogol::core::base_env;
using ogol::core::Lexer;
using ogol::core::Parser;
using ogol::core::TypeError;

TEST_CASE("Addition") {
  SECTION("No arguments") {
    Lexer lexer("(+)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(+ 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "1");
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(+ 1 2 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "6");
  }
  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(+ 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "3.0");
  }
  SECTION("Arguments of illegal type") {
    Lexer lexer("(+ 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), TypeError);
  }
}

TEST_CASE("Subtraction") {
  SECTION("No arguments") {
    Lexer lexer("(-)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(- 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "1");
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(- 1 2 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "-4");
  }
  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(- 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "-1.0");
  }
  SECTION("Arguments of illegal type") {
    Lexer lexer("(+ 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), TypeError);
  }
}

TEST_CASE("Multiplication") {
  SECTION("No arguments") {
    Lexer lexer("(*)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(* 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "1");
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(* 1 2 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "6");
  }
  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(* 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(std::stod(parser.parse().Eval(base_env).str()) == Approx(2.0));
  }
  SECTION("Arguments of illegal type") {
    Lexer lexer("(* 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), TypeError);
  }
}

TEST_CASE("Division") {
  SECTION("No arguments") {
    Lexer lexer("(/)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), ArgumentError);
  }

  SECTION("One argument") {
    Lexer lexer("(/ 1)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "1");
  }

  SECTION("Multiple arguments") {
    Lexer lexer("(/ 3 1 3)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().Eval(base_env).str() == "1");
  }

  SECTION("Arguments of mixed numerical type") {
    Lexer lexer("(/ 1 2.0)");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(std::stod(parser.parse().Eval(base_env).str()) == Approx(.5));
  }

  SECTION("Arguments of illegal type") {
    Lexer lexer("(/ 1 'a'')");
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse().Eval(base_env), TypeError);
  }
}

TEST_CASE("Defined identifier lookup") {
  Lexer lexer("((define x 3) x)");
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  REQUIRE(parser.parse().Eval(base_env).str() == "(nil 3)");
}
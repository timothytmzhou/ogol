#include <catch2/catch.hpp>
#include <core/exception.h>
#include <core/lexer.h>
#include <core/parser.h>

using ogol::core::ArgumentError;
using ogol::core::Lexer;
using ogol::core::Parser;
using ogol::core::TypeError;

TEST_CASE("Addition") {
  Lexer lexer;
  SECTION("No arguments") {
    "(+)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), ArgumentError);
  }

  SECTION("One argument") {
    "(+ 1)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "1");
  }

  SECTION("Multiple arguments") {
    "(+ 1 2 3)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "6");
  }
  SECTION("Arguments of mixed numerical type") {
    "(+ 1 2.0)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "3.0");
  }
  SECTION("Arguments of illegal type") {
    "(+ 1 'a'')" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), TypeError);
  }
}

TEST_CASE("Subtraction") {
  Lexer lexer;
  SECTION("No arguments") {
    "(-)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), ArgumentError);
  }

  SECTION("One argument") {
    "(- 1)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "1");
  }

  SECTION("Multiple arguments") {
    "(- 1 2 3)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "-4");
  }
  SECTION("Arguments of mixed numerical type") {
    "(- 1 2.0)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "-1.0");
  }
  SECTION("Arguments of illegal type") {
    "(+ 1 'a'')" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), TypeError);
  }
}

TEST_CASE("Multiplication") {
  Lexer lexer;
  SECTION("No arguments") {
    "(*)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), ArgumentError);
  }

  SECTION("One argument") {
    "(* 1)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "1");
  }

  SECTION("Multiple arguments") {
    "(* 1 2 3)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "6");
  }
  SECTION("Arguments of mixed numerical type") {
    "(* 1 2.0)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(std::stod(parser.parse().str()) == Approx(2.0));
  }
  SECTION("Arguments of illegal type") {
    "(* 1 'a'')" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), TypeError);
  }
}

TEST_CASE("Division") {
  Lexer lexer;
  SECTION("No arguments") {
    "(/)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), ArgumentError);
  }

  SECTION("One argument") {
    "(/ 1)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "1");
  }

  SECTION("Multiple arguments") {
    "(/ 3 1 3)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(parser.parse().str() == "1");
  }

  SECTION("Arguments of mixed numerical type") {
    "(/ 1 2.0)" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE(std::stod(parser.parse().str()) == Approx(.5));
  }

  SECTION("Arguments of illegal type") {
    "(/ 1 'a'')" >> lexer;
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.parse(), TypeError);
  }
}

TEST_CASE("Defined identifier lookup") {
  Lexer lexer;
  "((define x 3) x)" >> lexer;
  auto tokens = lexer.tokenize();
  Parser parser(tokens);
  REQUIRE(parser.parse().str() == "(nil 3)");
}
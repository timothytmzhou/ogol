#include <catch2/catch.hpp>
#include <core/exception.h>
#include <core/lexer.h>
#include <core/token.h>
#include <queue>

using ogol::core::Lexer;
using ogol::core::LexError;
using ogol::core::Token;
using ogol::core::TokenType;
using std::queue;

TEST_CASE("Whitespace characters between tokens is ignored") {
  Lexer lexer;
  SECTION("Single spaces") {
    "a b c" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "a"));
    expected.emplace(Token(TokenType::kIdentifier, "b"));
    expected.emplace(Token(TokenType::kIdentifier, "c"));

    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Multiple spaces") {
    "a    b  c" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "a"));
    expected.emplace(Token(TokenType::kIdentifier, "b"));
    expected.emplace(Token(TokenType::kIdentifier, "c"));

    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Mixed whitespace characters") {
    "a\n\t b   \nc" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "a"));
    expected.emplace(Token(TokenType::kIdentifier, "b"));
    expected.emplace(Token(TokenType::kIdentifier, "c"));

    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Trailing whitespace is ignored") {
    "a\n\t b   \nc      \n\n" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "a"));
    expected.emplace(Token(TokenType::kIdentifier, "b"));
    expected.emplace(Token(TokenType::kIdentifier, "c"));

    REQUIRE(lexer.tokenize() == expected);
  }
}

TEST_CASE("Integer tokenization") {
  Lexer lexer;
  SECTION("Positive integers") {
    "1 0 9" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kInteger, "1"));
    expected.emplace(Token(TokenType::kInteger, "0"));
    expected.emplace(Token(TokenType::kInteger, "9"));
    REQUIRE(lexer.tokenize() == expected);
  }
  SECTION("Negative integers") {
    "-1 -0 -9" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kInteger, "-1"));
    expected.emplace(Token(TokenType::kInteger, "-0"));
    expected.emplace(Token(TokenType::kInteger, "-9"));
    REQUIRE(lexer.tokenize() == expected);
  }
}

TEST_CASE("Real tokenization") {
  Lexer lexer;
  SECTION("Real with digits before decimal") {
    "3.1415" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kReal, "3.1415"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Real with no digit before decimal") {
    ".91" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kReal, ".91"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Negative reals") {
    "-.91 -3.14" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kReal, "-.91"));
    expected.emplace(Token(TokenType::kReal, "-3.14"));
    REQUIRE(lexer.tokenize() == expected);
  }
}
TEST_CASE("String tokenization") {
  Lexer lexer;
  SECTION("Single quoted strings") {
    "'In Mesoamerica, string was invented some 20,000 to 30,000 years ago'" >>
        lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kString,
                           "'In Mesoamerica, string was invented some "
                           "20,000 to 30,000 years ago'"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Double quoted strings") {
    R"("In Mesoamerica, string was invented some 20,000 to 30,000 years ago")" >>
        lexer;
    queue<Token> expected;
    expected.emplace(Token(
        TokenType::kString,
        R"("In Mesoamerica, string was invented some 20,000 to 30,000 years ago")"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Individual strings are tokenized individually") {
    R"("I like strings" "a lot")" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kString, "\"I like strings\""));
    expected.emplace(Token(TokenType::kString, "\"a lot\""));
    REQUIRE(lexer.tokenize() == expected);
  }
}

TEST_CASE("Identifier tokenization") {
  Lexer lexer;
  SECTION("Single-character symbolic identifiers") {
    "+ - * / < = > ! ^ | &" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "+"));
    expected.emplace(Token(TokenType::kIdentifier, "-"));
    expected.emplace(Token(TokenType::kIdentifier, "*"));
    expected.emplace(Token(TokenType::kIdentifier, "/"));
    expected.emplace(Token(TokenType::kIdentifier, "<"));
    expected.emplace(Token(TokenType::kIdentifier, "="));
    expected.emplace(Token(TokenType::kIdentifier, ">"));
    expected.emplace(Token(TokenType::kIdentifier, "!"));
    expected.emplace(Token(TokenType::kIdentifier, "^"));
    expected.emplace(Token(TokenType::kIdentifier, "|"));
    expected.emplace(Token(TokenType::kIdentifier, "&"));

    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Multi-character symbolic identifiers") {
    // not all of these will/are actual operators (just used for testing
    // purposes)
    "!= >> << +++ &=" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "!="));
    expected.emplace(Token(TokenType::kIdentifier, ">>"));
    expected.emplace(Token(TokenType::kIdentifier, "<<"));
    expected.emplace(Token(TokenType::kIdentifier, "+++"));
    expected.emplace(Token(TokenType::kIdentifier, "&="));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Alphabetical identifiers") {
    "x y foo" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "x"));
    expected.emplace(Token(TokenType::kIdentifier, "y"));
    expected.emplace(Token(TokenType::kIdentifier, "foo"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Alphanumeric identifiers") {
    "x1 y1" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "x1"));
    expected.emplace(Token(TokenType::kIdentifier, "y1"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Identifiers with underscores") {
    "i_luv_snake_case _uwu_" >> lexer;
    queue<Token> expected;
    expected.emplace(Token(TokenType::kIdentifier, "i_luv_snake_case"));
    expected.emplace(Token(TokenType::kIdentifier, "_uwu_"));
    REQUIRE(lexer.tokenize() == expected);
  }

  SECTION("Illegal identifiers starting with digits") {
    "0hno" >> lexer;
    REQUIRE_THROWS_AS(lexer.tokenize(), LexError);
  }

  SECTION("Illegal identifiers with mixed symbols/alphanumerics") {
    "+withsomeletters" >> lexer;
    REQUIRE_THROWS_AS(lexer.tokenize(), LexError);

    "someletterswith+" >> lexer;
    REQUIRE_THROWS_AS(lexer.tokenize(), LexError);
  }
}

TEST_CASE("Grouping character tokenization") {
  Lexer lexer;
  "( )" >> lexer;
  queue<Token> expected;
  expected.emplace(Token(TokenType::kGrouping, "("));
  expected.emplace(Token(TokenType::kGrouping, ")"));
  REQUIRE(lexer.tokenize() == expected);
}

TEST_CASE("Tokenization of mixed token types") {
  Lexer lexer;
  "1 2.0 xyz (" >> lexer;
  queue<Token> expected;
  expected.emplace(Token(TokenType::kInteger, "1"));
  expected.emplace(Token(TokenType::kReal, "2.0"));
  expected.emplace(Token(TokenType::kIdentifier, "xyz"));
  expected.emplace(Token(TokenType::kGrouping, "("));
  REQUIRE(lexer.tokenize() == expected);
}

TEST_CASE(
    "Distinct tokens without delimiting whitespace are separated correctly") {
  Lexer lexer;
  "(+ 1 2 3)" >> lexer;
  queue<Token> expected;
  expected.emplace(Token(TokenType::kGrouping, "("));
  expected.emplace(Token(TokenType::kIdentifier, "+"));
  expected.emplace(Token(TokenType::kInteger, "1"));
  expected.emplace(Token(TokenType::kInteger, "2"));
  expected.emplace(Token(TokenType::kInteger, "3"));
  expected.emplace(Token(TokenType::kGrouping, ")"));
  REQUIRE(lexer.tokenize() == expected);
}

TEST_CASE("Lexer stream operators loading in source") {
  SECTION("Stream operators work bidirectionally") {
    Lexer lexer1;
    "1 2 3" >> lexer1;
    Lexer lexer2;
    lexer2 << "1 2 3";
    REQUIRE(lexer1.tokenize() == lexer2.tokenize());
  }
}

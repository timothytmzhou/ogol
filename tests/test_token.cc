#include <catch2/catch.hpp>
#include <core/token.h>

using ogol::core::Token;
using ogol::core::TokenType;

TEST_CASE("Token comparison") {
  SECTION("Identical tokens") {
    REQUIRE(Token(TokenType::kGrouping, "(") ==
            Token(TokenType::kGrouping, "("));
  }

  SECTION("Different values same token type") {
    REQUIRE(Token(TokenType::kInteger, "1") != Token(TokenType::kInteger, "2"));
  }

  SECTION("Same values different token type") {
    REQUIRE(Token(TokenType::kInteger, "1") != Token(TokenType::kReal, "1"));
  }
}

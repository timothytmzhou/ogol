#include <catch2/catch.hpp>
#include <visualizer/turtle.h>

using ogol::visualizer::Turtle;

bool vect_compare(const ivec2 &v1, const ivec2 &v2) {
  return (v1.x == v2.x) && (v1.y == v2.y);
}

TEST_CASE("Position of turtle is updated correctly") {
  SECTION("Speed is positive") {
    Turtle turtle({0, 0}, // position
                  {0, 1}, // orientation
                  2,      // speed
                  1,      // turn speed
                  10,     // max x
                  10      // max y
    );
    REQUIRE(vect_compare(turtle.GetPosition(), {0, 2}));
  }
  SECTION("Speed is negative") {
    Turtle turtle({0, 0}, // position
                  {0, 1}, // orientation
                  -2,     // speed
                  1,      // turn speed
                  10,     // max x
                  10      // max y
    );
    REQUIRE(vect_compare(turtle.GetPosition(), {0, -2}));
  }
}

TEST_CASE("Turtle tries to go out of bounds") {
  SECTION("Turtle at top of screen") {
    Turtle turtle({0, 10}, // position
                  {0, 1},  // orientation
                  1,       // speed
                  1,      // turn speed
                  10,      // max x
                  10       // max y
    );
    REQUIRE(vect_compare(turtle.GetPosition(), {0, 10}));
  }
  SECTION("Turtle at bottom of screen") {
    Turtle turtle({0, -10}, // position
                  {0, -1},  // orientation
                  1,        // speed
                  1,      // turn speed
                  10,       // max x
                  10        // max y
    );
    REQUIRE(vect_compare(turtle.GetPosition(), {0, -10}));
  }
  SECTION("Turtle at right side of screen") {
    Turtle turtle({10, 0}, // position
                  {1, 0},  // orientation
                  1,       // speed
                  1,      // turn speed
                  10,      // max x
                  10       // max y
    );
    REQUIRE(vect_compare(turtle.GetPosition(), {10, 0}));
  }
  SECTION("Turtle at left side of screen") {
    Turtle turtle({-10, 0}, // position
                  {-1, 0},  // orientation
                  1,        // speed
                  1,      // turn speed
                  10,       // max x
                  10        // max y
    );
    REQUIRE(vect_compare(turtle.GetPosition(), {-10, 0}));
  }
}

TEST_CASE("Turtle rotation") {
  SECTION("Positive number of degrees") {
    Turtle turtle({0, 0}, // position
                  {0, 1}, // orientation
                  1,      // speed
                  1,      // turn speed
                  10,     // max x
                  10      // max y
    );
    turtle.Rotate(90);
    REQUIRE(vect_compare(turtle.GetPosition(), {-1, 0}));
  }
  SECTION("Negative number of degrees") {
    Turtle turtle({0, 0}, // position
                  {0, 1}, // orientation
                  1,      // speed
                  1,      // turn speed
                  10,     // max x
                  10      // max y
    );
    turtle.Rotate(-90);
    REQUIRE(vect_compare(turtle.GetPosition(), {1, 0}));
  }
}
#pragma once

#include "cinder/gl/gl.h"

using ci::Color;
using glm::dvec2;
using glm::ivec2;
using std::string;
using std::vector;

namespace ogol::visualizer {

/**
 * Class to represent a turtle object, a cursor with orientation and a speed.
 */
class Turtle {
 public:
  Turtle() = default;
  /**
   * Constructor which initializes turtle with given position, orientation and
   * speed.
   */
  Turtle(const dvec2 &position, const dvec2 &forward, double speed,
         size_t max_x, size_t max_y);
  void Clear();
  vector<ivec2> GetPath() const;
  /**
   * Gets the (discrete) position of the turtle.
   */
  ivec2 GetPosition();
  /**
   * Gets the color of the turtle.
   */
  ci::Color GetColor();
  /**
   * Updates the position of the turtle based on its orientation.
   */
  void Update();
  /**
   * Rotates the turtle by theta degrees.
   */
  void Rotate(double theta);
  /**
   * Sets the color of the turtle.
   */
  void SetColor(const ci::Color &color);
  /**
   * Sets the speed of the turtle.
   */
  void SetSpeed(double speed);
  /**
   * Gets a string representation of the turtle.
   */
  string str() const;

 private:
  dvec2 position_{0, 0};
  // stores the points the turtle has been to
  vector<ivec2> traversed;
  // unit vector representing the turtle's forward direction
  dvec2 forward_{0, 1};
  double speed_ = 1;
  size_t max_x_;
  size_t max_y_;
  ci::Color color_ = "black";
};

} // namespace ogol::visualizer
#pragma once

#include "cinder/gl/gl.h"

using ci::Color;
using glm::dvec2;
using glm::ivec2;
using std::string;
using std::vector;

struct TurtleState {
  ivec2 position;
  double rotation;
  Color color = "black";
};

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
         double turn_speed, size_t max_x, size_t max_y);
  void Clear();
  [[nodiscard]] vector<TurtleState> GetPath() const;
  /**
   * Move the turtle forward by x pixels.
   */
  void Forward(size_t x);
  /**
   * Rotates the turtle by theta degrees.
   */
  void Rotate(double theta);
  /**
   * Sets the speed of the turtle.
   */
  void SetSpeed(double speed);
  /**
   * Sets the color of the turtle.
   */
  void SetColor(const Color &color);
  /**
   * Gets a string representation of the turtle.
   */
  string str() const;

private:
  double speed_ = 5;
  double turn_speed_ = 30;
  size_t max_x_ = 500;
  size_t max_y_ = 500;
  // the turtle's current state
  TurtleState state_;
  // stores past TurtleStates
  vector<TurtleState> path_;

  void PushState();
};

} // namespace ogol::visualizer
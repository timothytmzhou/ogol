#include "visualizer/turtle.h"
#include <sstream>

using std::map;
using std::stringstream;

namespace ogol::visualizer {

Turtle::Turtle(const dvec2 &position, const dvec2 &forward, double speed,
               double turn_speed, size_t max_x, size_t max_y)
    : speed_(speed), turn_speed_(turn_speed), max_x_(max_x),
      max_y_(max_y), state_{position, 0} {}

void Turtle::Clear() { *this = Turtle(); }

vector<TurtleState> Turtle::GetPath() const { return path_; }

void Turtle::PushState() { path_.push_back(state_); }

void Turtle::Forward(size_t x) {
  size_t num_steps = x / speed_;
  // north is 0 degrees in our coordinate system
  double theta = glm::radians(state_.rotation + 90);
  dvec2 step_velocity =
      ((double)x / num_steps) * ci::dvec2{glm::cos(theta), glm::sin(theta)};
  for (size_t i = 0; i < num_steps; ++i) {
    state_.position += step_velocity;
    // clamp position within range
    state_.position.x =
        std::clamp(state_.position.x, -(int)max_x_, (int)max_x_);
    state_.position.y =
        std::clamp(state_.position.y, -(int)max_y_, (int)max_y_);
    PushState();
  }
}

void Turtle::Rotate(double theta) {
  size_t num_steps = theta / turn_speed_;
  double dt = theta / num_steps;
  for (size_t i = 0; i < num_steps; ++i) {
    state_.rotation += dt;
    if (state_.rotation < 0) {
      state_.rotation += 360;
    } else if (state_.rotation >= 360) {
      state_.rotation -= 360;
    }
    PushState();
  }
}

void Turtle::SetSpeed(double speed) { speed_ = speed; }

string Turtle::str() const {
  stringstream ss;
  ss << "Turtle position: " << state_.position << "\n";
  ss << "Rotation: " << state_.rotation << "\n";
  ss << "Speed: " << speed_ << "\n";
  ss << "Color: " << state_.color << "\n";
  return ss.str();
}

void Turtle::SetColor(const Color &color) { state_.color = color; }

ivec2 Turtle::GetPosition() const { return state_.position; }

} // namespace ogol::visualizer

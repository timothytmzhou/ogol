#include "visualizer/turtle.h"
#include <sstream>

using std::stringstream;

namespace ogol::visualizer {

Turtle::Turtle(const dvec2 &position, const dvec2 &forward, double speed,
               size_t max_x, size_t max_y)
    : position_(position), forward_(forward), speed_(speed), max_x_(max_x),
      max_y_(max_y) {}

ivec2 Turtle::GetPosition() { return position_; }

ci::Color Turtle::GetColor() { return color_; }

void Turtle::Update() {
  position_ += speed_ * forward_;
  // clamp position within range
  position_.x = std::clamp(position_.x, -(double)max_x_, (double)max_x_);
  position_.y = std::clamp(position_.y, -(double)max_y_, (double)max_y_);
}

void Turtle::Rotate(double theta) {
  forward_ = glm::rotate(forward_, glm::radians(theta));
}

void Turtle::SetColor(const ci::Color &color) { color_ = color; }

void Turtle::SetSpeed(double speed) { speed_ = speed; }
string Turtle::str() const {
  stringstream ss;
  ss << "Turtle position: " << position_ << "\n";
  ss << "Facing: " << forward_ << "\n";
  ss << "Speed: " << speed_ << "\n";
  ss << "Color: " << color_ << "\n";
  return ss.str();
}

} // namespace ogol::visualizer

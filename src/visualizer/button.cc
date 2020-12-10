#include "visualizer/button.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include <utility>

using ci::gl::drawSolidRect;
using ci::gl::drawStrokedRect;

namespace ogol::visualizer {

Button::Button(const ivec2 &pos, size_t width, size_t height,
               const Color &color, const Color &outline_color,
               ci::Font text_font, string text, function<void(void)> action)
    : pos_(pos), width_(width), height_(height), color_(color),
      outline_color_(outline_color), text_font_(std::move(text_font)),
      text_(std::move(text)),
      r_(Rectf(pos[0] - width / 2, pos[1] - height / 2, pos[0] + width / 2,
               pos[1] + height / 2)),
      action_(std::move(action)) {}

void Button::HandleMouseDown(ci::app::MouseEvent event) {
  if (IsClicked(event.getPos())) {
    action_();
  }
}

void Button::Draw() {
  ci::gl::color(color_);
  drawSolidRect(r_);
  ci::gl::color(outline_color_);
  drawStrokedRect(r_);
  ci::gl::drawStringCentered(text_, ivec2{pos_[0], 10}, outline_color_,
                             text_font_);
}

bool Button::IsClicked(const ci::vec2 &mouse_coords) const {
  return mouse_coords.x > r_.x1 && mouse_coords.y > r_.y1 &&
         mouse_coords.x < r_.x2 && mouse_coords.y < r_.y2;
}

} // namespace ogol::visualizer

#pragma once

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

#include <visualizer/model.h>

using std::function;
using std::string;

using ci::Color;
using ci::Rectf;
using glm::ivec2;

using ogol::visualizer::Model;

namespace ogol::visualizer {
/**
 * Class to represent a clickable button.
 */
class Button {
public:
  /**
   * Constructor which takes in the position, width, height, and style
   * parameters for the button as well as lambda mutating a Model which is
   * called when clicked.
   */
  Button(const ivec2 &pos, size_t width, size_t height, const Color &color,
         const Color &outline_color, ci::Font text_font, string text,
         function<void(void)> action);
  /**
   * Draws the button to the screen.
   */
  void Draw();
  /**
   * Checks if the mouse has clicked the button--if it has, run its action.
   */
  void HandleMouseDown(ci::app::MouseEvent event);

private:
  const ivec2 pos_;
  const size_t width_;
  const size_t height_;
  const Color color_;
  const Color outline_color_;
  const ci::Font text_font_;
  const string text_;
  const Rectf r_;

  const function<void(void)> action_;

  /**
   * Helper method that checks if button has been clicked.
   */
  bool IsClicked(const ci::vec2 &mouse_coords) const;
};

} // namespace ogol::visualizer
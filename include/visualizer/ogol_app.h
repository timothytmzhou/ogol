#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "visualizer/turtle.h"

namespace ogol {

namespace visualizer {
/**
 * Main logic for rendering turtle graphics to the screen.
 */
class GraphicsRenderer : public ci::app::App {
public:
  GraphicsRenderer();
  void draw() override;

  const size_t kWindowWidth = 1920;
  const size_t kWindowHeight = 1080;

private:
  Turtle turtle_ =
      Turtle({0, 0}, {1, 0}, 1, kWindowWidth / 2, kWindowHeight / 2);
  ivec2 prev_;
  ivec2 current_;
};

} // namespace visualizer

} // namespace ogol

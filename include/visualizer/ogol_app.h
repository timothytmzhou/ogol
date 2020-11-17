#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace ogol {

namespace visualizer {
/**
 * Main logic for rendering turtle graphics to the screen.
 */
class GraphicsRenderer : public ci::app::App {
public:
  void draw() override;

  const size_t kWindowWidth = 1920;
  const size_t kWindowHeight = 1080;

private:
};

} // namespace visualizer

} // namespace ogol

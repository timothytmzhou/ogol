#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "core/interpreter.h"

#include "visualizer/button.h"
#include "visualizer/model.h"
#include "visualizer/turtle.h"

using ci::Color;
using std::string;

using ogol::core::Interpreter;
using ogol::visualizer::Model;

namespace ogol::visualizer {
/**
 * Main logic for rendering turtle graphics to the screen.
 */
class GraphicsRenderer : public ci::app::App {
public:
  GraphicsRenderer();
  void setup() override;
  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;

  const size_t kWindowWidth = 1100;
  const size_t kWindowHeight = 1000;

private:
  // model
  Model model_;
  // view
  const size_t kTopBarHeight = 80;
  const size_t kRunButtonWidth = 200;
  const Color kTextColor = Color("black");
  const Color kButtonColor = Color::gray(0.9f);
  // controller
  Button run_button_;
};

} // namespace ogol::visualizer

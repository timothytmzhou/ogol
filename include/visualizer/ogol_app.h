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
  bool is_rendering_ = false;
  // view
  const size_t kTopBarHeight = 40;
  const Color kOutlineColor = Color("black");
  const Color kButtonColor = Color::gray(0.9f);
  vector<TurtleState> states_;
  size_t current_state_index_ = 0;
  // controller
  Button run_button_;
  string kScriptsDir = "/home/timothy/documents/";
  vector<string> kExtensions = {".ogl"};

  void SetStates(const vector<TurtleState> &states);
  void RenderGraphics();
  ivec2 ToScreenSpace(const ivec2 &coord) const;

  string GetPath() const;
};

} // namespace ogol::visualizer

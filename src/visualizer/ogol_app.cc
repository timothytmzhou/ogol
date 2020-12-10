#include "visualizer/ogol_app.h"
#include "cinder/gl/gl.h"

namespace ogol::visualizer {

ogol::visualizer::GraphicsRenderer::GraphicsRenderer()
    : run_button_(ivec2{kWindowWidth / 2, kTopBarHeight / 2}, kRunButtonWidth,
                  kTopBarHeight, kButtonColor, kTextColor,
                  ci::Font("Roboto", 20), "run", [this]() {
                    SetStates(model_.Run());
                    model_.Clear();
                  }) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void GraphicsRenderer::setup() {}

void GraphicsRenderer::draw() {
  ci::gl::clear(Color("white"));
  Render();
  if (!is_rendering_) {
    run_button_.Draw();
  }
}

void GraphicsRenderer::SetStates(const vector<TurtleState> &states) {
  is_rendering_ = true;
  states_ = states;
  current_state_index_ = 0;
}

void GraphicsRenderer::mouseDown(ci::app::MouseEvent event) {
  if (!is_rendering_) {
    run_button_.HandleMouseDown(event);
  }
}
void GraphicsRenderer::Render() {
  for (size_t i = 1; i < current_state_index_; ++i) {
    ci::gl::color(states_[i].color);
    ci::gl::drawLine(ToScreenSpace(states_[i - 1].position),
                     ToScreenSpace(states_[i].position));
  }
  if (current_state_index_ == states_.size()) {
    is_rendering_ = false;
  } else {
    ++current_state_index_;
  }
}
ivec2 GraphicsRenderer::ToScreenSpace(const ivec2 &coord) const {
  return ivec2{coord.x + kWindowWidth / 2, kWindowHeight / 2 - coord.y};
}

} // namespace ogol::visualizer

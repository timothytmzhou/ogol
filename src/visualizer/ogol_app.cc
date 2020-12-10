#include "visualizer/ogol_app.h"
#include "cinder/gl/gl.h"

namespace ogol::visualizer {

ogol::visualizer::GraphicsRenderer::GraphicsRenderer()
    : run_button_(ivec2{kWindowWidth / 2, kTopBarHeight / 2}, kRunButtonWidth,
                  kTopBarHeight, kButtonColor, kTextColor,
                  ci::Font("Roboto", 20), "run", [this]() {
                    model_.Run();
                  }) {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void GraphicsRenderer::setup() {

}

void GraphicsRenderer::draw() {
  ci::gl::clear(Color("white"));
  run_button_.Draw();


}

void GraphicsRenderer::mouseDown(ci::app::MouseEvent event) {
  run_button_.HandleMouseDown(event);
}

} // namespace ogol::visualizer

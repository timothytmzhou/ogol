#include "cinder/gl/gl.h"
//#include "cinder/cairo/Cairo.h"

#include "visualizer/ogol_app.h"

namespace ogol::visualizer {

ogol::visualizer::GraphicsRenderer::GraphicsRenderer() {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void GraphicsRenderer::draw() {
//  prev_ = turtle_.GetPosition();
//  turtle_.Update();
//  current_ = turtle_.GetPosition();
//  // code derived from
//  // https://github.com/cinder/Cinder/blob/master/samples/CairoBasic/src/CairoBasicApp.cpp
//  cairo::Context ctx(cairo::createWindowSurface());
//  renderScene(ctx);
}

} // namespace ogol::visualizer

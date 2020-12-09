#include <visualizer/ogol_app.h>

void prepareSettings(
    ogol::visualizer::GraphicsRenderer::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ogol::visualizer::GraphicsRenderer, ci::app::RendererGl,
           prepareSettings)

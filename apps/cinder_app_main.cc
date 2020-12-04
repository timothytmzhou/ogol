#include <visualizer/ideal_gas_app.h>

void prepareSettings(
    ideal_gas::visualizer::IdealGasRenderer::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ideal_gas::visualizer::IdealGasRenderer, ci::app::RendererGl,
           prepareSettings)

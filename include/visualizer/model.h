#pragma once

#include "cinder/gl/gl.h"
#include <core/interpreter.h>

using std::function;
using std::string;
using std::vector;

using glm::ivec2;

using ogol::core::Interpreter;

namespace ogol::visualizer {

class Model {
public:
  /**
   * Sets the file the model will run.
   */
  void SetFile(const string& path);
  /**
   * Resets the state of the turtle.
   */
  void Clear();
  /**
   * Runs the current file, returns a vector of points the turtle visited.
   */
  vector<ivec2> Run();

private:
  // TODO: remove hardcoded path
  string path_ = "/home/timothy/Documents/main.ogl";
  Turtle turtle_;
  Interpreter interpreter_;
};

} // namespace ogol::visualizer
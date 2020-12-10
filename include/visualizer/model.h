#pragma once

#include <cinder/gl/gl.h>
#include <core/interpreter.h>

using std::function;
using std::string;
using std::vector;

using glm::ivec2;

using ogol::core::Interpreter;

namespace ogol::visualizer {

/**
 * Class which manages and runs selected source files.
 */
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
  vector<TurtleState> Run();

private:
  string path_;
  Turtle turtle_;
  Interpreter interpreter_;
};

} // namespace ogol::visualizer
#include <fstream>
#include <visualizer/model.h>

using std::ifstream;

namespace ogol::visualizer {

void visualizer::Model::SetFile(const string &path) { path_ = path; }

void Model::Clear() { turtle_.Clear(); }

vector<TurtleState> Model::Run() {
  ifstream source(path_);
  source >> interpreter_;
  interpreter_.Run(&turtle_);
  return turtle_.GetPath();
}

} // namespace ogol::visualizer
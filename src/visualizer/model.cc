#include <fstream>
#include <visualizer/model.h>

using std::ifstream;

namespace ogol::visualizer {

void visualizer::Model::SetFile(const string &path) { path_ = path; }

void Model::Clear() {
  turtle_.clear();
}

vector<ivec2> Model::Run() {
  ifstream source("/home/timothy/Documents/main.ogl");
  source >> interpreter_;
  interpreter_.Run(&turtle_);
  return turtle_.GetPath();
}


} // namespace ogol::visualizer
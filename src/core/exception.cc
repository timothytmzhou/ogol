#include "core/exception.h"

#include <utility>

namespace ogol::core {

OgolError::OgolError(string msg) : msg_(std::move(msg)) {}
const char *OgolError::what() const noexcept { return msg_.c_str(); }

} // namespace ogol::core
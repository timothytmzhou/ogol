#include "core/exception.h"

#include "boost/format.hpp"
#include <utility>

namespace ogol::core {

OgolError::OgolError(const string &msg, size_t line_num)
    : msg_(boost::str(boost::format("Error at line %i. %s") % line_num % msg)),
      line_num_(line_num) {}

const char *OgolError::what() const noexcept { return msg_.c_str(); }

} // namespace ogol::core
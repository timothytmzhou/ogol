#include "core/token.h"

namespace ogol::core {

bool operator==(const Token &a, const Token &b) {
  return a.value == b.value && a.token_type == b.token_type;
}

bool operator!=(const Token &a, const Token &b) {
  return !(a == b);
}

} // namespace ogol::core
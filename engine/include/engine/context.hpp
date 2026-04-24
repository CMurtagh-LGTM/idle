#pragma once

#include "engine/sprite.hpp"

#include <expected>
#include <vector>

namespace engine {

class Context {
public:
  enum class ContextError {
    MakeAppError,
  };

  Context();
  std::expected<void, ContextError> start();

private:
  std::vector<internal::Sprite> sprites;
};

} // namespace engine

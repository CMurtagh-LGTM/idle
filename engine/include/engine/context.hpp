#pragma once

#include "engine/sprite.hpp"

#include <vector>

namespace engine {

class Context {
public:
  Context();
  void start();
private:
  std::vector<internal::Sprite> sprites;
};

} // namespace engine

#pragma once

#include <cute.h>

namespace engine {

class Sprite {
public:
  Sprite(const char* path);

private:
  CF_Sprite *ptr;
};

} // namespace engine

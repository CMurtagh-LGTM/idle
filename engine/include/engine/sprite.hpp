#pragma once

#include <cute.h>

namespace engine {

class Sprite {
public:
  Sprite(const char* path);

  int get_width();
  int get_height();
  void set_scale(CF_V2 scale);
  void set_offset(CF_V2 offset);
private:
  CF_Sprite *ptr;
};

} // namespace engine

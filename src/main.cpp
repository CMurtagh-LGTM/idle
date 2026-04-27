#include "engine/engine.h"
#include "engine/sprite.hpp"

#include <cute.h>

int main() {

  engine::Sprite sprite{"content/person.png"};
  float x = 0;

  engine::connect_process([&](float delta_time) {
    sprite.set_offset(V2(x, 0));
    x += delta_time * 10;
  });

  engine::start();

  return 0;
}

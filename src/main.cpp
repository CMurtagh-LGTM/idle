#include "engine/engine.hpp"
#include "engine/layout/text.hpp"
#include "engine/layout/vertical_box.hpp"
#include "engine/sprite.hpp"

#include <cute.h>

int main() {

  engine::Sprite sprite{"content/person.png"};
  float x = 0;

  engine::connect_process([&](float delta_time) {
    sprite.set_offset(V2(x, 0));
    x += delta_time * 10;
  });

  engine::layout::VerticalBox v_box;
  v_box.add_child(std::make_shared<engine::layout::Text>("hi"));
  v_box.add_child(std::make_shared<engine::layout::Text>("bye"));
  v_box.set_position(V2(-100, 0));

  engine::layout::Text text{"test", V2(0, 0)};

  engine::start();

  return 0;
}

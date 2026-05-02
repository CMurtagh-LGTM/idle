#include "engine/engine.hpp"
#include "engine/layout/image.hpp"
#include "engine/layout/root.hpp"
#include "engine/layout/text.hpp"
#include "engine/layout/vertical_box.hpp"
#include "engine/shape.hpp"
#include "engine/sprite.hpp"

#include <cute.h>

int main() {
  engine::Sprite sprite{"content/person.png"};
  float x = 0;

  engine::connect_process([&](float delta_time) {
    sprite.set_offset(V2(x, 0));
    x += delta_time * 10;
  });

  std::shared_ptr<engine::layout::VerticalBox> v_box = std::make_shared<engine::layout::VerticalBox>();
  v_box->add_child(std::make_shared<engine::layout::Text>("hi"));
  v_box->add_child(std::make_shared<engine::layout::Image>("content/person.png"));
  v_box->add_child(std::make_shared<engine::layout::Text>("bye"));
  engine::layout::Root root{v_box, V2(-100, 0)};

  engine::layout::Text text{"test", V2(0, 0)};
  engine::Box box{Cute::make_aabb(V2(0, 0), 32, 32)};
  engine::Box box_filled{Cute::make_aabb(V2(0, 100), 32, 32), true};

  engine::start();

  return 0;
}

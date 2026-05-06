#include "engine/engine.hpp"
#include "engine/layout/image.hpp"
#include "engine/layout/panel.hpp"
#include "engine/layout/root.hpp"
#include "engine/layout/text.hpp"
#include "engine/layout/vertical_box.hpp"

int main() {
  std::shared_ptr<engine::layout::VerticalBox> v_box = std::make_shared<engine::layout::VerticalBox>();
  v_box->add_child(engine::make_shared<engine::layout::Text>("hi", {Cute::color_white()}));
  v_box->add_child(std::make_shared<engine::layout::Image>("content/person.png"));
  std::shared_ptr<engine::layout::Panel> panel =
      engine::make_shared<engine::layout::Panel>({engine::component::FILL, Cute::color_white()});
  panel->set_child(engine::make_shared<engine::layout::Text>("panel", {Cute::color_black()}));
  v_box->add_child(panel);
  v_box->add_child(engine::make_shared<engine::layout::Text>("bye", {Cute::color_white()}));
  std::shared_ptr<engine::layout::Panel> panel2 = engine::make_shared<engine::layout::Panel>({Cute::color_white()});
  panel2->set_child(std::make_shared<engine::layout::Image>("content/person.png"));
  v_box->add_child(panel2);
  engine::layout::Root root{v_box, V2(-100, 100)};

  auto shape = engine::component::ShapePtr(std::in_place_type<engine::internal::Box>, Cute::make_aabb(V2(0, 0), 10, 10),
                                           engine::component::BoxSettings{Cute::color_white()});

  engine::start();

  return 0;
}

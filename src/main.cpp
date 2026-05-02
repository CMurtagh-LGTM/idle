#include "engine/engine.hpp"
#include "engine/layout/image.hpp"
#include "engine/layout/panel.hpp"
#include "engine/layout/root.hpp"
#include "engine/layout/text.hpp"
#include "engine/layout/vertical_box.hpp"

#include <cute.h>

int main() {
  std::shared_ptr<engine::layout::VerticalBox> v_box = std::make_shared<engine::layout::VerticalBox>();
  v_box->add_child(std::make_shared<engine::layout::Text>("hi"));
  v_box->add_child(std::make_shared<engine::layout::Image>("content/person.png"));
  std::shared_ptr<engine::layout::Panel> panel = std::make_shared<engine::layout::Panel>();
  panel->set_child(std::make_shared<engine::layout::Text>("panel"));
  v_box->add_child(panel);
  v_box->add_child(std::make_shared<engine::layout::Text>("bye"));
  std::shared_ptr<engine::layout::Panel> panel2 = std::make_shared<engine::layout::Panel>();
  panel2->set_child(std::make_shared<engine::layout::Image>("content/person.png"));
  v_box->add_child(panel2);
  engine::layout::Root root{v_box, V2(-100, 100)};

  engine::start();

  return 0;
}

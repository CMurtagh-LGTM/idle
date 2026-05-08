#include "engine/component/timer.hpp"
#include "engine/engine.hpp"
#include "engine/layout/button.hpp"
#include "engine/layout/image.hpp"
#include "engine/layout/panel.hpp"
#include "engine/layout/root.hpp"
#include "engine/layout/text.hpp"
#include "engine/layout/vertical_box.hpp"
#include "engine/utils/property.hpp"
#include "engine/utils/tween.hpp"

int main() {
  auto v_box = std::make_shared<engine::layout::VerticalBox>();

  v_box->add_child(engine::make_shared<engine::layout::Text>("hi", {Cute::color_white()}));

  v_box->add_child(std::make_shared<engine::layout::Image>("content/person.png"));

  auto panel = engine::make_shared<engine::layout::Panel>({engine::component::FILL, Cute::color_white()});
  auto button = engine::make_shared<engine::layout::Button>();
  button->connect_on_clicked([](Cute::v2) { engine::utils::log("hi"); });
  button->set_child(engine::make_shared<engine::layout::Text>("button", {Cute::color_black()}));
  panel->set_child(button);
  v_box->add_child(panel);

  auto bye_property = engine::utils::Property<float>(0);
  auto bye = engine::make_shared<engine::layout::Text>("", {Cute::color_white()});
  bye_property.connect(sigc::mem_fun(*bye, &engine::layout::Text::set_value<float>));
  v_box->add_child(bye);
  auto panel2 = engine::make_shared<engine::layout::Panel>({Cute::color_white()});

  engine::utils::tween(bye_property, 100.0F, 10);

  panel2->set_child(std::make_shared<engine::layout::Image>("content/person.png"));
  v_box->add_child(panel2);

  engine::layout::Root root{v_box, V2(-100, 100)};

  auto shape = engine::component::ShapePtr(engine::component::MAKE_BOX, Cute::make_aabb(V2(0, 0), 10, 10),
                                           engine::component::BoxSettings{Cute::color_white()});

  int tweened_value = 0;
  auto timer = engine::component::TimerPtr(engine::component::Interval(1));
  timer->connect([&] { engine::utils::log("Tick: {}", tweened_value); });

  engine::utils::tween(tweened_value, 100, 10);

  engine::start();

  return 0;
}

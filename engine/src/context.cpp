#include "internal/context.hpp"

#include "engine/utils/utils.hpp"
#include "internal/system/clickbox_manager.hpp"
#include "internal/system/manager.hpp"
#include "internal/system/shape_manager.hpp"
#include "internal/system/sprite_manager.hpp"
#include "internal/system/text_manager.hpp"
#include "internal/system/timer_manager.hpp"

#include <cute_app.h>
#include <cute_draw.h>
#include <cute_file_system.h>
#include <cute_input.h>
#include <cute_math.h>
#include <cute_result.h>
#include <cute_time.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::internal {

namespace {
void mount_content_folder() {
  Cute::CF_Path path = Cute::fs_get_base_directory();
  path.normalize();
  path += "../content";
  utils::log("Mounting path {}", path.c_str());
  Cute::fs_mount(path.c_str(), "/content");
}
} // namespace

Context::Context() {
  constexpr int width = 640;
  constexpr int height = 480;
  const CF_Result result = Cute::make_app(
      "Fancy Window Title", 0, 0, 0, width, height,
      CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT | CF_APP_OPTIONS_FILE_SYSTEM_DONT_DEFAULT_MOUNT_BIT, nullptr);
  utils::check_cf_result(result);

  mount_content_folder();
  Cute::make_font("/content/ProggyClean.ttf", "ProggyClean");
}

Context::~Context() { Cute::destroy_app(); }

// NOLINTNEXTLINE(readability-function-size)
void Context::update() {
  Cute::app_update();

  if (cf_mouse_down(CF_MOUSE_BUTTON_LEFT)) {
    auto screen_click = V2(Cute::mouse_x(), Cute::mouse_y());
    handle_mouse(std::get<ClickBoxManager>(managers), Cute::screen_to_world(screen_click));
  }

  handle_ticks(std::get<TimerManager>(managers));

  process.emit(CF_DELTA_TIME);

  draw_contents(std::get<ShapeManager>(managers));
  draw_contents(std::get<TextManager>(managers));
  draw_contents(std::get<SpriteManager>(managers));

  Cute::app_draw_onto_screen(true);
}

namespace {
void emloop(void * context) {
  static_cast<Context *>(context)->update();
}
}

void Context::start() {
  Cute::push_font("ProggyClean");
#ifdef CF_EMSCRIPTEN
  emscripten_set_main_loop_arg(&emloop, this, 60, true);
#else
  while (Cute::app_is_running()) {
    update();
  }
#endif
  Cute::pop_font();
}

sigc::connection Context::connect_process(const sigc::slot<void(float)>& slot) { return process.connect(slot); }
sigc::connection Context::connect_process(sigc::slot<void(float)>&& slot) { return process.connect(std::move(slot)); }

Context& ContextBroker::context() {
  static Context context{};
  return context;
}

} // namespace engine::internal

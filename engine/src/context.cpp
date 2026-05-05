#include "internal/context.hpp"

#include "engine/utils.hpp"
#include "internal/shape_manager.hpp"
#include "internal/sprite_manager.hpp"
#include "internal/text_manager.hpp"

#include <cute_app.h>
#include <cute_draw.h>
#include <cute_file_system.h>
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
      CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT | CF_APP_OPTIONS_FILE_SYSTEM_DONT_DEFAULT_MOUNT_BIT, "idle");
  utils::check_cf_result(result);

  mount_content_folder();
  Cute::make_font("/content/ProggyClean.ttf", "ProggyClean");
}

Context::~Context() { Cute::destroy_app(); }

void Context::start() {
  Cute::push_font("ProggyClean");
  while (Cute::app_is_running()) {
    process.emit(CF_DELTA_TIME);

    Cute::app_update();

    shape_manager.draw();
    text_manager.draw();
    sprite_manager.draw();

    Cute::app_draw_onto_screen(true);
  }
  Cute::pop_font();
}

sigc::connection Context::connect_process(const sigc::slot<void(float)>& slot) { return process.connect(slot); }
sigc::connection Context::connect_process(sigc::slot<void(float)>&& slot) { return process.connect(std::move(slot)); }

Context& ContextBroker::context() {
  static Context context{};
  return context;
}

} // namespace engine::internal

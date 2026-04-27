#include "engine/context.hpp"

#include "proggy.h"
#include "engine/utils.hpp"

#include <cute.h>

namespace engine {

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
  CF_Result result =
      Cute::make_app("Fancy Window Title", 0, 0, 0, width, height,
                     CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT |
                         CF_APP_OPTIONS_FILE_SYSTEM_DONT_DEFAULT_MOUNT_BIT,
                     "idle");
  utils::check_cf_result(result);

  mount_content_folder();
  Cute::make_font_from_memory(static_cast<void *>(proggy_data), proggy_sz,
                              "ProggyClean");

}

Context::~Context() {
  Cute::destroy_app();
}

void Context::start() {
  while (Cute::app_is_running()) {
    process.emit(CF_DELTA_TIME);

    Cute::app_update();
    // Cute::push_font("ProggyClean");
    // Cute::draw_text("hello", V2(-25, -50));
    // Cute::pop_font();

    sprite_manager.draw_sprites();

    Cute::app_draw_onto_screen(true);
  }
}

internal::SpriteManager& Context::get_sprite_manager() {
  return sprite_manager;
}

void start() {
  return internal::ContextBroker::context().start();
}

Context& internal::ContextBroker::context() {
    static Context context{};
    return context;
}

} // namespace engine

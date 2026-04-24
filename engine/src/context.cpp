#include "engine/context.hpp"

#include "proggy.h"

#include <cute.h>
#include <imgui.h>


namespace engine {

Context::Context() {

}

std::expected<void, Context::ContextError> Context::start() {
    constexpr int width = 640;
    constexpr int height = 480;
    // Create a window with a resolution of 640 x 480.
    CF_Result result = Cute::make_app("Fancy Window Title", 0, 0, 0, width, height, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "idle");
    if (Cute::is_error(result)) {
        printf("Error: %s\n", result.details);
        return std::unexpected(ContextError::MakeAppError);
    }

    Cute::make_font_from_memory(proggy_data, proggy_sz, "ProggyClean");

    CF_Sprite girl_sprite = Cute::make_demo_sprite();
    Cute::sprite_play(girl_sprite, "idle");
    girl_sprite.scale = V2(4,4);

    while (Cute::app_is_running())
    {
        Cute::app_update();
        Cute::push_font("ProggyClean");

        Cute::draw_text("hello", V2(-25, -50));

        Cute::sprite_update(girl_sprite);
        Cute::sprite_draw(girl_sprite);

        Cute::app_draw_onto_screen();
    }

    Cute::destroy_app();

    return std::expected<void, Context::ContextError>();
}

}

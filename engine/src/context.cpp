#include <cute.h>
#include "engine/context.hpp"


namespace engine {

Context::Context() {

}

void Context::start() {
    // Create a window with a resolution of 640 x 480.
    CF_Result result = Cute::make_app("Fancy Window Title", 0, 0, 0, 640, 480, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "idle");
    if (Cute::is_error(result)) {
        printf("Error: %s\n", result.details);
        return;
    }

    CF_Sprite girl_sprite = Cute::make_demo_sprite();
    Cute::sprite_play(girl_sprite, "idle");
    girl_sprite.scale = V2(4,4);

    while (Cute::app_is_running())
    {
        Cute::app_update();

        Cute::sprite_update(girl_sprite);
        Cute::sprite_draw(girl_sprite);

        Cute::app_draw_onto_screen();
    }

    Cute::destroy_app();
}

}

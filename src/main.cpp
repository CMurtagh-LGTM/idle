#include "engine/context.hpp"
#include "engine/sprite.hpp"

#include <cute.h>

int main() {

    engine::Sprite sprite{"content/person.png"};
    float x = 0;

    engine::internal::ContextBroker::context().process.connect([&](float dt){
        sprite.set_offset(V2(x, 0));
        x += dt * 10;
    });

    engine::start();

    return 0;
}

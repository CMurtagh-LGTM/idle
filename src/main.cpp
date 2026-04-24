#include "engine/context.hpp"

int main() {

    engine::Context context;

    auto e = context.start();

    if (e) {
        return 0;
    } else {
        return 1;
    }

}

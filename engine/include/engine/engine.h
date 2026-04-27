#pragma once

#include <sigc++/sigc++.h>

namespace engine {

void start();
sigc::connection connect_process(const sigc::slot<void(float)> &slot);
sigc::connection connect_process(sigc::slot<void(float)> &&slot);

}

#pragma once

#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>

namespace engine {

/// Starts the main loop, will return when the game is exiting
void start();

/// Register a callback that will be run at the start of the main loop
sigc::connection connect_process(const sigc::slot<void(float)>& slot);
/// Register a callback that will be run at the start of the main loop
sigc::connection connect_process(sigc::slot<void(float)>&& slot);

} // namespace engine

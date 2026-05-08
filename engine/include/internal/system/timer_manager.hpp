#pragma once

#include "engine/utils/utils.hpp"
#include "internal/config.hpp"
#include "internal/system/manager.hpp"

#include <sigc++/signal.h>

namespace engine::internal {

class Timer {
public:
  class Interval : public utils::integral_t<float> {
    using utils::integral_t<float>::integral_t;
  };
  class Offset : public utils::integral_t<float> {
    using utils::integral_t<float>::integral_t;
    static Offset now();
  };
  explicit Timer(Interval new_interval, Offset new_offset = Offset(0));
  sigc::connection connect(const sigc::slot<void()>& on_tick);
  sigc::connection connect(sigc::slot<void()>&& on_tick);
  void handle_tick();

private:
  float interval;
  float offset;
  sigc::signal<void()> tick;
};

using TimerManager = Manager<TIMER_COUNT, Timer>;

void handle_ticks(TimerManager& timer_manager);

} // namespace engine::internal

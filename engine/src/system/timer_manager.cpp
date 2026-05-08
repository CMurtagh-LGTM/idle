#include "internal/system/timer_manager.hpp"

#include <cute_time.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::internal {

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
Timer::Timer(Interval new_interval, Offset new_offset) : interval(new_interval), offset(new_offset) {}

sigc::connection Timer::connect(const sigc::slot<void()>& on_tick) { return tick.connect(on_tick); }
sigc::connection Timer::connect(sigc::slot<void()>&& on_tick) { return tick.connect(std::move(on_tick)); }

void Timer::handle_tick() {
  if (Cute::on_interval(interval, offset)) {
    tick.emit();
  }
}

void handle_ticks(TimerManager& timer_manager) {
  for (Timer& timer : timer_manager) {
    timer.handle_tick();
  }
}

Timer::Offset Timer::Offset::now() {
  return Offset(static_cast<float>(CF_SECONDS)); // NOLINT(modernize-return-braced-init-list)
}

} // namespace engine::internal

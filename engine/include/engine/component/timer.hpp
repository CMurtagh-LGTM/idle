#pragma once

#include "internal/managed_ptr.hpp"
#include "internal/timer_manager.hpp"

namespace engine::component {

using Interval = internal::Timer::Interval;
using Offset = internal::Timer::Offset;

using TimerPtr = internal::ManagedPtr<internal::Timer>;

} // namespace engine::component

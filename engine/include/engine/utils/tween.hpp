#pragma once

#include "engine/engine.hpp"
#include "engine/utils/lerp.hpp"
#include "engine/utils/utils.hpp"

#include <memory>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <sigc++/signal.h>
#include <utility>

namespace engine::utils {

template <typename T> void tween(T& value, T target, float duration);

/// Lerps between two values over a duration of time
template <typename T> class Tween {
public:
  using value_type = T;

  void operator()([[maybe_unused]] float frame_time) noexcept {
    float time = (now() - start_time) / duration;

    // End the tween when finished
    if (time >= 1) {
      connection->disconnect();
      return;
    }

    *ptr = utils::lerp(start_value, end_value, time);
  }

private:
  Tween(value_type& value, value_type target, float new_duration, std::shared_ptr<sigc::connection> connection_ref)
      : ptr(&value), start_value(value), end_value(target), start_time(now()), duration(new_duration),
        connection(std::move(connection_ref)) {}

  value_type* ptr;
  value_type start_value;
  value_type end_value;
  float start_time;
  float duration;

  std::shared_ptr<sigc::connection> connection;

  friend void tween<value_type>(value_type& value, value_type target, float duration);
};

template <typename T> void tween(T& value, T target, float duration) {
  auto connection = std::make_shared<sigc::connection>();
  *connection = connect_process(Tween(value, target, duration, connection));
}

} // namespace engine::utils

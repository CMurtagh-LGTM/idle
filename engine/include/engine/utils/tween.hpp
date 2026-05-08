#pragma once

#include "engine/engine.hpp"
#include "engine/utils/lerp.hpp"
#include "engine/utils/property.hpp"
#include "engine/utils/utils.hpp"

#include <memory>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <sigc++/signal.h>
#include <utility>

namespace engine::utils {

template <typename C, typename T>
std::shared_ptr<sigc::connection> tween(C& value, T target, float duration)
  requires(std::is_convertible_v<C, T>);

/// Lerps between two values over a duration of time
template <typename C, typename T>
  requires(std::is_convertible_v<C, T>)
class Tween {
public:
  using container_type = C;
  using value_type = T;

  void operator()([[maybe_unused]] float frame_time) noexcept {
    float time = (now() - start_time) / duration;

    // End the tween when finished
    if (time >= 1) {
      *ptr = end_value;
      connection->disconnect();
      return;
    }

    *ptr = utils::lerp(start_value, end_value, time);
  }

private:
  Tween(container_type& value, value_type target, float new_duration, std::shared_ptr<sigc::connection> connection_ref)
      : ptr(&value), start_value(value), end_value(target), start_time(now()), duration(new_duration),
        connection(std::move(connection_ref)) {}

  container_type* ptr;
  value_type start_value;
  value_type end_value;
  float start_time;
  float duration;

  std::shared_ptr<sigc::connection> connection;

  friend std::shared_ptr<sigc::connection> tween<container_type, value_type>(container_type& value, value_type target,
                                                                             float duration);
};

template <typename C, typename T>
std::shared_ptr<sigc::connection> tween(C& value, T target, float duration)
  requires(std::is_convertible_v<C, T>)
{
  auto connection = std::make_shared<sigc::connection>();
  *connection = connect_process(Tween(value, target, duration, connection));
  return connection;
}

} // namespace engine::utils

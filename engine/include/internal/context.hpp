#pragma once

#include "internal/system/clickbox_manager.hpp"
#include "internal/system/shape_manager.hpp"
#include "internal/system/sprite_manager.hpp"
#include "internal/system/text_manager.hpp"
#include "internal/system/timer_manager.hpp"
#include "internal/system/transform_manager.hpp"

#include <sigc++/signal.h>

namespace engine::internal {

class ContextBroker;

/// The overall context of the game
class Context {
public:
  ~Context();
  Context(const Context&) = delete;
  Context(Context&&) = delete;
  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  /// Starts the main loop, will return when the game is exiting
  void start();
  /// Register a callback that will be run at the start of the main loop
  sigc::connection connect_process(const sigc::slot<void(float)>& slot);
  /// Register a callback that will be run at the start of the main loop
  sigc::connection connect_process(sigc::slot<void(float)>&& slot);

  /// Get the manger that manges objects of type `T`
  template <typename T> auto& get_manager() { // NOLINT(readability-function-size)
    // TODO use expansion from c++26 when it arrives in clang
    if constexpr (std::is_same_v<T, SpriteManager::value_type>) {
      return std::get<SpriteManager>(managers);
    }
    if constexpr (std::is_same_v<T, ShapeManager::value_type> ||
                  utils::contains_variant_type_v<T, ShapeManager::value_type>) {
      return std::get<ShapeManager>(managers);
    }
    if constexpr (std::is_same_v<T, TextManager::value_type>) {
      return std::get<TextManager>(managers);
    }
    if constexpr (std::is_same_v<T, TransformManager::value_type>) {
      return std::get<TransformManager>(managers);
    }
    if constexpr (std::is_same_v<T, ClickBoxManager::value_type>) {
      return std::get<ClickBoxManager>(managers);
    }
    if constexpr (std::is_same_v<T, TimerManager::value_type>) {
      return std::get<TimerManager>(managers);
    }
  }

private:
  Context();
  friend internal::ContextBroker;

  sigc::signal<void(float)> process;

  std::tuple<SpriteManager, TextManager, ShapeManager, TransformManager, ClickBoxManager, TimerManager> managers;
};

/// Holds a global `Context`
class ContextBroker {
public:
  /// Get the global `Context`
  static Context& context();
};

} // namespace engine::internal

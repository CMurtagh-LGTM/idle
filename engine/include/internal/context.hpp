#pragma once

#include "internal/shape_manager.hpp"
#include "internal/sprite_manager.hpp"
#include "internal/text_manager.hpp"
#include "internal/transform_manager.hpp"

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
  template <typename T> auto& get_manager() {
    if constexpr (std::is_same_v<T, SpriteManager::value_type>) {
      return sprite_manager;
    }
    if constexpr (utils::contains_variant_type_v<T, ShapeManager::value_type>) {
      return shape_manager;
    }
    if constexpr (std::is_same_v<T, TextManager::value_type>) {
      return text_manager;
    }
    if constexpr (std::is_same_v<T, TransformManager::value_type>) {
      return transform_manager;
    }
  }

private:
  Context();
  friend internal::ContextBroker;

  sigc::signal<void(float)> process;

  internal::SpriteManager sprite_manager;
  internal::TextManager text_manager;
  internal::ShapeManager shape_manager;
  internal::TransformManager transform_manager;
};

/// Holds a global `Context`
class ContextBroker {
public:
  /// Get the global `Context`
  static Context& context();
};

} // namespace engine::internal

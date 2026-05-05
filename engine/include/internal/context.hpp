#pragma once

#include "internal/shape_manager.hpp"
#include "internal/sprite_manager.hpp"
#include "internal/text_manager.hpp"

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

  /// The sprite manager managers all the sprites drawn
  SpriteManager& get_sprite_manager();
  /// The text manager managers all the text drawn
  TextManager& get_text_manager();
  /// The shape manager managers all the shapes drawn
  ShapeManager& get_shape_manager();

  template <typename T> auto& get_manager() {
    if constexpr (utils::contains_type_v<T, SpriteManager::value_type>) {
      return sprite_manager;
    }
    if constexpr (std::constructible_from<ShapeManager::value_type, T>) {
      return shape_manager;
    }
  }

private:
  Context();
  friend internal::ContextBroker;

  sigc::signal<void(float)> process;

  internal::SpriteManager sprite_manager;
  internal::TextManager text_manager;
  internal::ShapeManager shape_manager;
};

/// Holds a global `Context`
class ContextBroker {
public:
  /// Get the global `Context`
  static Context& context();
};

} // namespace engine::internal

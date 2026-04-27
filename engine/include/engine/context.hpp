#pragma once

#include "internal/sprite_manager.hpp"

#include <sigc++/sigc++.h>

namespace engine {

namespace internal {
class ContextBroker;
}

class Context {
public:
  ~Context();
  Context(const Context&) = delete;
  Context(Context&&) = delete;
  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  void start();

  internal::SpriteManager& get_sprite_manager();

  sigc::signal<void(float)> process;

private:
  Context();

  internal::SpriteManager sprite_manager;

  friend internal::ContextBroker;
};

void start();

namespace internal {
class ContextBroker {
  public:
    static Context& context();
};
} // namespace internal

} // namespace engine

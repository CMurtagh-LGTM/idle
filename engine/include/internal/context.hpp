#pragma once

#include "internal/sprite_manager.hpp"

#include <sigc++/sigc++.h>

namespace engine::internal {

class ContextBroker;

class Context {
public:
  ~Context();
  Context(const Context&) = delete;
  Context(Context&&) = delete;
  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  void start();
  sigc::connection connect_process(const sigc::slot<void(float)>& slot);
  sigc::connection connect_process(sigc::slot<void(float)>&& slot);

  internal::SpriteManager& get_sprite_manager();

private:
  Context();
  friend internal::ContextBroker;

  sigc::signal<void(float)> process;

  internal::SpriteManager sprite_manager;
};

class ContextBroker {
public:
  static Context& context();
};

} // namespace engine::internal

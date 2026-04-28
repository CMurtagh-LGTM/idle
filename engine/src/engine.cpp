#include "engine/engine.hpp"
#include "internal/context.hpp"

namespace engine {

void start() { internal::ContextBroker::context().start(); }
sigc::connection connect_process(const sigc::slot<void(float)>& slot) {
  return internal::ContextBroker::context().connect_process(slot);
}
sigc::connection connect_process(sigc::slot<void(float)>&& slot) {
  return internal::ContextBroker::context().connect_process(std::move(slot));
}

} // namespace engine

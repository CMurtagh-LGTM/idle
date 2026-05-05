#pragma once

#include "internal/context.hpp"

#include <gsl/gsl>

namespace engine::internal {

template <typename T> class ManagedPtr {
private:
  using manager_t = std::remove_cvref_t<decltype(internal::ContextBroker::context().get_manager<T>())>;

public:
  static constexpr bool IS_VARIANT = manager_t::IS_VARIANT;
  using value_type = manager_t::value_type;

  template <typename... Args>
  explicit ManagedPtr(Args... args)
      : ptr(internal::ContextBroker::context().get_manager<T>().template create<T>(args...)) {}

  ManagedPtr(const ManagedPtr&) = delete;
  ManagedPtr(ManagedPtr&&) = delete;
  ManagedPtr& operator=(const ManagedPtr&) = delete;
  ManagedPtr& operator=(ManagedPtr&&) = delete;

  ~ManagedPtr() { internal::ContextBroker::context().get_manager<T>().free(ptr); }

  T& operator*() { return *get(); }
  const T& operator*() const { return *get(); }

  T* operator->() { return get(); }
  const T* operator->() const { return get(); }

private:
  T* get() {
    if constexpr (IS_VARIANT) {
      return &std::get<T>(*ptr);
    } else {
      return ptr; // NOLINT(cppcoreguidelines-owning-memory)
    }
  }
  [[nodiscard]] const T* get() const {
    if constexpr (IS_VARIANT) {
      return &std::get<T>(*ptr);
    } else {
      return ptr; // NOLINT(cppcoreguidelines-owning-memory)
    }
  }

  gsl::owner<value_type*> ptr;
};

} // namespace engine::internal

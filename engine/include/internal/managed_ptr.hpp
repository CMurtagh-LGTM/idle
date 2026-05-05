#pragma once

#include "internal/context.hpp"

#include <gsl/gsl>

namespace engine::internal {

// TODO have IS_SHARED be an attribute rather than a template parameter
template <typename T, bool IS_SHARED> class ManagedPtr {
private:
  using manager_t = std::remove_cvref_t<decltype(internal::ContextBroker::context().get_manager<T>())>;

public:
  static constexpr bool IS_VARIANT = manager_t::IS_VARIANT;
  using value_type = manager_t::value_type;

  template <typename... Args>
  explicit ManagedPtr(Args... args)
      : ptr(internal::ContextBroker::context().get_manager<T>().template create<T>(args...)) {
    if constexpr (IS_SHARED) {
      ptr->increment_count();
    }
  }

  ManagedPtr(ManagedPtr&&) = delete;
  ManagedPtr& operator=(ManagedPtr&&) = delete;

  ManagedPtr(const ManagedPtr&)
    requires(!IS_SHARED)
  = delete;
  ManagedPtr& operator=(const ManagedPtr&)
    requires(!IS_SHARED)
  = delete;
  ManagedPtr(const ManagedPtr& other)
    requires IS_SHARED
      : ptr(other.ptr) {
    ptr->increment_count();
  };
  ManagedPtr& operator=(const ManagedPtr& other)
    requires IS_SHARED
  {
    if (!ptr->decrement_count()) {
      internal::ContextBroker::context().get_manager<T>().free(ptr);
    }
    ptr = other.ptr;
    ++(ptr->ref_count);
  };

  ~ManagedPtr()
    requires(!IS_SHARED)
  {
    internal::ContextBroker::context().get_manager<T>().free(ptr);
  }
  ~ManagedPtr()
    requires IS_SHARED
  {
    if (!ptr->decrement_count()) {
      internal::ContextBroker::context().get_manager<T>().free(ptr);
    }
  }

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

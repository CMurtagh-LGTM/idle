#pragma once

#include "internal/context.hpp"

#include <gsl/gsl>

namespace engine::internal {

template <typename T> class ManagedPtr {
private:
  using manager_t = std::remove_cvref_t<decltype(internal::ContextBroker::context().get_manager<T>())>;
  using block_t = manager_t::Block;

public:
  static constexpr bool IS_VARIANT = manager_t::IS_VARIANT;
  using value_type = manager_t::value_type;

  template <typename... Args>
  explicit ManagedPtr(Args... args)
      : ptr(internal::ContextBroker::context().get_manager<T>().template create<T>(args...)) {
    ++(ptr->accounting.ref_count);
  }

  ManagedPtr() : ptr(nullptr) {};

  ManagedPtr(ManagedPtr&& other) noexcept : ptr(std::exchange(other.ptr, nullptr)) {}
  ManagedPtr& operator=(ManagedPtr&& other) noexcept {
    clean_ptr();
    ptr = std::exchange(other.ptr, nullptr); // NOLINT(cppcoreguidelines-owning-memory)
  }

  ManagedPtr(const ManagedPtr& other) : ptr(other.ptr) {
    if (ptr != nullptr) {
      ++(ptr->accounting.ref_count);
    }
  }
  ManagedPtr& operator=(const ManagedPtr& other) {
    clean_ptr();
    ptr = other.ptr;
    ++(ptr->ref_count);
  };

  ~ManagedPtr() { clean_ptr(); }

  T& operator*() { return *get(); }
  const T& operator*() const { return *get(); }

  T* operator->() { return get(); }
  const T* operator->() const { return get(); }

private:
  T* get() {
    if constexpr (IS_VARIANT) {
      return &std::get<T>(ptr->value);
    } else {
      return &ptr->value; // NOLINT(cppcoreguidelines-owning-memory)
    }
  }
  [[nodiscard]] const T* get() const {
    if constexpr (IS_VARIANT) {
      return &std::get<T>(ptr->value);
    } else {
      return &ptr->value; // NOLINT(cppcoreguidelines-owning-memory)
    }
  }

  void clean_ptr() {
    if (ptr == nullptr) {
      return;
    }
    --(ptr->accounting.ref_count);
    if (ptr->accounting.ref_count <= 0) {
      internal::ContextBroker::context().get_manager<T>().free(ptr);
    }
  }

  gsl::owner<block_t*> ptr;
};

} // namespace engine::internal

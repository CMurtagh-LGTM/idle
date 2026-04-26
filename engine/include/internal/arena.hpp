#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <gsl/gsl>

namespace engine::internal {

template <typename T> class Arena {
public:
  using value_type = T;
  using pointer = T *;

  Arena(size_t n)
      : arena(static_cast<pointer>(malloc(n * sizeof(T)))) // NOLINT(cppcoreguidelines-no-malloc)
#ifndef NDEBUG
        ,
        count(n)
#endif
  {
  }
  ~Arena() { free(arena); }
  Arena(const Arena &) = delete;
  Arena(Arena &&) = delete;
  Arena &operator=(const Arena &) = delete;
  Arena &operator=(Arena &&) = delete;

  [[nodiscard]] gsl::not_null<pointer> new_ptr() {
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    return new (allocate()) value_type;
  }

  [[nodiscard]] gsl::not_null<pointer> copy(pointer ptr) {
    pointer new_ptr = allocate();
    *new_ptr = *ptr;
    return new_ptr;
  }

  pointer begin() {
    return arena;
  }
  pointer end() {
    return arena + index + 1;
  }

private:
  [[nodiscard]] gsl::not_null<pointer> allocate() {
    ++index;
    assert(index < count);
    return arena + index;
  }

  T *arena = nullptr;
  size_t index = -1;
#ifndef NDEBUG
  size_t count = 0;
#endif
};

} // namespace engine::internal

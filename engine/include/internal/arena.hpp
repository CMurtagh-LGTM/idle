#pragma once

#include <cassert>
#include <cstdlib>
#include <gsl/gsl>

namespace engine::internal {

template <typename T, int SIZE> class Arena {
public:
  using value_type = T;
  using pointer = T*;
  using difference_type = std::pointer_traits<pointer>::difference_type;

  Arena()
      : arena(static_cast<pointer>(malloc(SIZE * sizeof(T)))) // NOLINT(cppcoreguidelines-no-malloc)
  {}
  ~Arena() { free(arena); }
  Arena(const Arena&) = delete;
  Arena(Arena&&) = delete;
  Arena& operator=(const Arena&) = delete;
  Arena& operator=(Arena&&) = delete;

  [[nodiscard]] gsl::owner<pointer> new_ptr() { return new (allocate()) value_type; }

  [[nodiscard]] gsl::owner<pointer> copy(gsl::not_null<pointer> ptr) {
    gsl::owner<pointer> new_ptr = allocate();
    *new_ptr = *ptr;
    return new_ptr;
  }

  void delete_ptr(gsl::owner<pointer> ptr) { delete ptr; }

  pointer begin() { return arena; }
  pointer end() { return arena + next_free; }

private:
  [[nodiscard]] gsl::owner<pointer> allocate() {
    assert(next_free < SIZE);
    assert(used_elements[next_free] == false);
    used_elements[next_free] = true;
    pointer ptr = arena + next_free;
    while (used_elements[next_free]) {
      ++next_free;
    }
    return ptr;
  }

  void deallocate(gsl::owner<pointer> ptr) {
    difference_type index = ptr - arena;
    assert(used_elements[index] == true);
    used_elements[index] = false;
    next_free = std::min(index, next_free);
  }

  T* arena = nullptr;
  std::array<bool, SIZE> used_elements{};
  difference_type next_free = 0;
};

} // namespace engine::internal

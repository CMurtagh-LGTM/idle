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

  class Iterator {
  public:
    Iterator(Arena* arena) : arena_ptr(arena) {}
    Iterator(Arena* arena, difference_type start_index) : arena_ptr(arena), index(start_index) {}

    value_type& operator*() { return *(arena_ptr->arena + index); }

    Iterator& operator++() {
      ++index;
      while(index <= arena_ptr->last_element && !arena_ptr->used_elements[index]) {
        ++index;
      }
      return *this;
    }

    bool operator==(const Iterator& other) const { return arena_ptr == other.arena_ptr && index == other.index; }

  private:
    gsl::not_null<Arena*> arena_ptr;
    difference_type index = 0;
  };

  using iterator = Iterator;
  using const_iterator = const Iterator;

  iterator begin() { return iterator(this); }
  iterator end() { return iterator(this, last_element + 1); }
  const_iterator begin() const { return iterator(this); }
  const_iterator end() const { return iterator(this, last_element + 1); }

private:
  [[nodiscard]] gsl::owner<pointer> allocate() {
    assert(next_free < SIZE);
    assert(used_elements[next_free] == false);

    used_elements[next_free] = true;

    pointer ptr = arena + next_free;

    last_element = std::max(last_element, next_free);

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

    while (!used_elements[last_element]) {
      --last_element;
    }
  }

  T* arena = nullptr;
  std::array<bool, SIZE> used_elements{};
  difference_type next_free = 0;
  difference_type last_element = 0;
};

} // namespace engine::internal

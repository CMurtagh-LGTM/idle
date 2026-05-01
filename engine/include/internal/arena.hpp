#pragma once

#include <cassert>
#include <cstdlib>
#include <gsl/gsl>

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
// NOLINTBEGIN(cppcoreguidelines-no-malloc)

namespace engine::internal {

/// An arena with a maximum size of `SIZE` where elements of `T` can be allocated
template <typename T, int SIZE> class Arena {
public:
  using value_type = T;
  using pointer = T*;
  using difference_type = std::pointer_traits<pointer>::difference_type;

  /// Allocates the arena but does not initialise any elements
  Arena() : arena(static_cast<pointer>(malloc(SIZE * sizeof(T)))) {}
  ~Arena() { free(arena); }
  Arena(const Arena&) = delete;
  Arena(Arena&&) = delete;
  Arena& operator=(const Arena&) = delete;
  Arena& operator=(Arena&&) = delete;

  /// Allocates a new element within the arena and initialises with `args`
  template <typename... Args> [[nodiscard]] gsl::owner<pointer> new_ptr(Args... args) {
    return new (allocate()) value_type(args...);
  }

  /// Allocates a new element and copies the object stored at `other`
  [[nodiscard]] gsl::owner<pointer> copy(const value_type& other) {
    gsl::owner<pointer> new_ptr = allocate();
    *new_ptr = other;
    return new_ptr;
  }

  /// Destructs and deallocates the element that `ptr` points to
  void delete_ptr(gsl::owner<pointer> ptr) {
    ptr->~value_type();
    deallocate(ptr);
  }

  /// Iterates over all allocated members of the arena
  class Iterator {
  public:
    using value_type = Arena<T, SIZE>::value_type;
    using difference_type = Arena<T, SIZE>::difference_type;
    explicit Iterator(Arena* arena) : arena_ptr(arena) {}
    Iterator(Arena* arena, difference_type start_index) : arena_ptr(arena), index(start_index) {}

    value_type& operator*() const { return *(arena_ptr->arena + index); }

    Iterator& operator++() {
      ++index;
      while (index <= arena_ptr->last_element && !arena_ptr->used_elements[index]) {
        ++index;
      }
      return *this;
    }
    void operator++(int) { ++*this; }

    bool operator==(const Iterator& other) const { return arena_ptr == other.arena_ptr && index == other.index; }

  private:
    gsl::not_null<Arena*> arena_ptr;
    difference_type index = 0;
  };

  using iterator = Iterator;
  using const_iterator = std::const_iterator<Iterator>;

  /// Iterator to the start of the arena, iterating over allocated elements
  [[nodiscard]] iterator begin() { return iterator(this); }
  /// Iterator to past end of the arena, iterating over allocated elements
  [[nodiscard]] iterator end() { return iterator(this, last_element + 1); }
  /// Iterator to the start of the arena, iterating over allocated elements
  [[nodiscard]] const_iterator begin() const { return iterator(this); }
  /// Iterator to past end of the arena, iterating over allocated elements
  [[nodiscard]] const_iterator end() const { return iterator(this, last_element + 1); }

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
    const difference_type index = ptr - arena;
    assert(used_elements[index] == true);
    used_elements[index] = false;

    next_free = std::min(index, next_free);

    while (!used_elements[last_element] && last_element < 0) {
      --last_element;
    }
  }

  gsl::owner<T*> arena = nullptr;
  std::array<bool, SIZE> used_elements{};
  difference_type next_free = 0;
  difference_type last_element = 0;
};

} // namespace engine::internal

// NOLINTEND(cppcoreguidelines-no-malloc)
// NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

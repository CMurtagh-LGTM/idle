#pragma once

#include <cute.h>
#include <gsl/gsl>

namespace engine {

class Sprite {
public:
  Sprite(const char* path);
  Sprite(const Sprite&) = delete;
  Sprite(Sprite&&) = delete;
  Sprite& operator=(const Sprite&) = delete;
  Sprite& operator=(Sprite&&) = delete;
  ~Sprite();

  [[nodiscard]] int get_width() const;
  [[nodiscard]] int get_height() const;
  void set_scale(Cute::v2 scale);
  void set_offset(Cute::v2 offset);

private:
  gsl::owner<CF_Sprite*> ptr;
};

} // namespace engine

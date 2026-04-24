#pragma once

namespace engine {
namespace internal {

class Sprite {
public:
  Sprite();

private:
//   raylib::Texture m_texture;
};

} // namespace internal

class Sprite {
public:
  Sprite();

private:
  internal::Sprite *m_ptr;
};

} // namespace engine

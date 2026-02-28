#pragma once

#include <glad/gl.h>

#include "Core/Utils.hpp"

namespace Jupiter::Renderer {
static inline constexpr u32 GetSizeOfType(u32 type) {
  switch (type) {
  case GL_FLOAT:
    return sizeof(float);
  case GL_UNSIGNED_INT:
    return sizeof(unsigned int);
  case GL_UNSIGNED_BYTE:
    return sizeof(unsigned char);
  default:
    return 0;
  }
}
} // namespace Jupiter::Renderer

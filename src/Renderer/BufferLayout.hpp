#pragma once

#include <string>
#include <vector>

#include "Core/Utils.hpp"
#include "Renderer/RenderUtils.hpp"

namespace Jupiter::Renderer {
struct BufferElement {
  std::string name;
  u32 type, count, offset; // type: GL_FLOAT for example
  bool normalized;
};

class BufferLayout {
public:
  BufferLayout() = delete;
  BufferLayout(std::initializer_list<BufferElement> data) : m_Data(data) {
    u32 offset = 0;
    for (auto &element : m_Data) {
      element.offset = offset;
      offset += element.count * GetSizeOfType(element.type);
    }
    m_Stride = offset;
  }

  const std::vector<BufferElement> &GetElements() const { return m_Data; }
  u32 GetStride() const { return m_Stride; }

private:
  std::vector<BufferElement> m_Data;
  u32 m_Stride = 0;
};
} // namespace Jupiter::Renderer

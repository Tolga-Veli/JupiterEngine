#pragma once

#include <vector>
#include <glad/gl.h>
#include "Core/Utils.hpp"

namespace Jupiter::Renderer {
class IndexBuffer {
public:
  IndexBuffer() = delete;
  IndexBuffer(const std::vector<u32> &indices) : m_Count(indices.size()) {
    glGenBuffers(1, &m_IndexBufferID);

    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32),
                 indices.data(), GL_STATIC_DRAW);
  }

  ~IndexBuffer() { glDeleteBuffers(1, &m_IndexBufferID); }

  void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID); }
  void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

  u32 GetCount() const { return m_Count; }

private:
  u32 m_IndexBufferID;
  std::size_t m_Count;
};
}; // namespace Jupiter::Renderer

#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Core/Utils.hpp"
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace Jupiter::Renderer {
class VertexArray {
public:
  VertexArray() { glGenVertexArrays(1, &m_Array); }
  ~VertexArray() { glDeleteVertexArrays(1, &m_Array); }

  void Bind() const { glBindVertexArray(m_Array); }
  void Unbind() const { glBindVertexArray(0); }

  void SetVertexBuffer(const VertexBuffer &vb, const BufferLayout &layout) {
    Bind();
    vb.Bind();

    const auto &elements = layout.GetElements();
    for (u32 i = 0; i < elements.size(); i++) {
      const auto &[name, type, count, offset, normalized] = elements[i];
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, count, type, normalized ? GL_TRUE : GL_FALSE,
                            layout.GetStride(),
                            (const void *)(uintptr_t)offset);
    }

    Unbind();
    vb.Unbind();
  }

  void SetIndexBuffer(const IndexBuffer &ib) {
    Bind();
    ib.Bind();

    m_IndexBuffer = &ib;

    Unbind();
    ib.Unbind();
  }

private:
  u32 m_Array;
  const IndexBuffer *m_IndexBuffer = nullptr;
};
}; // namespace Jupiter::Renderer

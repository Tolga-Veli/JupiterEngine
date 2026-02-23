#pragma once

#include "Core/Utils.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Jupiter::Renderer {
class VertexBuffer {
public:
  VertexBuffer() = delete;
  VertexBuffer(const std::vector<float> &vertices) {
    glGenBuffers(1, &m_VertBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);
  }

  VertexBuffer(const VertexBuffer &) = delete;
  VertexBuffer &operator=(const VertexBuffer &) = delete;

  ~VertexBuffer() { glDeleteBuffers(1, &m_VertBuffer); }

  void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer); }
  void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
  u32 m_VertBuffer;
};
}; // namespace Jupiter::Renderer

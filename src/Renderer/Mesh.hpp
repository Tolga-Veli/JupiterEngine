#pragma once

#include <vector>

#include "Core/Utils.hpp"

#include "VertexArray.hpp"

namespace Jupiter::Renderer {

struct Vertex {
  float pos[3];
  float uv[2];
  float light_level;
};

class Mesh {
public:
  Mesh() = delete;

  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;
  Mesh(Mesh &&) noexcept = default;
  Mesh &operator=(Mesh &&) noexcept = default;

  Mesh(const std::vector<float> &vertices, const std::vector<u32> &indices,
       const BufferLayout &layout)
      : m_VertexBuffer(vertices), m_IndexBuffer(indices) {
    m_VertexArray.SetVertexBuffer(m_VertexBuffer, layout);
    m_VertexArray.SetIndexBuffer(m_IndexBuffer);
    m_IndexCount = indices.size();
  }

  void Bind() const { m_VertexArray.Bind(); }
  void Unbind() const { m_VertexArray.Unbind(); }

  u32 GetIndexCount() const { return m_IndexCount; }

private:
  VertexArray m_VertexArray;
  VertexBuffer m_VertexBuffer;
  IndexBuffer m_IndexBuffer;
  u32 m_IndexCount = 0;
};

} // namespace Jupiter::Renderer
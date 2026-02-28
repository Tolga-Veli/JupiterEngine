#pragma once

#include "Core/Utils.hpp"

#include "Shader.hpp"
#include "Texture2D.hpp"

namespace Jupiter::Renderer {

class Material {
public:
  Material() = delete;

  Material(const Material &) = delete;
  Material &operator=(const Material &) = delete;
  Material(Material &&) = delete;
  Material &operator=(Material &&) = delete;

  void Bind() const { m_Shader->Bind(); }

private:
  std::string m_Name;

  std::shared_ptr<Shader> m_Shader;
  std::shared_ptr<Texture2D> m_Texture;
};
} // namespace Jupiter::Renderer
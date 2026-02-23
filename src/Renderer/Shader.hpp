#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <filesystem>

#include "Core/Utils.hpp"

namespace Jupiter {
namespace Renderer {

constexpr u32 SHADER_TYPE_COUNT = 5;
enum class ShaderType : u32 {
  None = 0,
  Vertex = 1, // GL_VERTEX_SHADER,
  Fragment,   // GL_FRAGMENT_SHADER,
  Geometry,   // GL_GEOMETRY_SHADER,
  Compute,    // GL_COMPUTE_SHADER,
};

inline constexpr std::string_view to_string(ShaderType type) {
  switch (type) {
  case ShaderType::None:
    return "None";
  case ShaderType::Vertex:
    return "Vertex";
  case ShaderType::Fragment:
    return "Fragment";
  case ShaderType::Geometry:
    return "Geometry";
  case ShaderType::Compute:
    return "Compute";
  default:
    return "";
  }
}

namespace OpenGL {
inline constexpr i32 GetShaderStage(ShaderType type) {
  switch (type) {
  case ShaderType::Vertex:
    return GL_VERTEX_SHADER;
  case ShaderType::Fragment:
    return GL_FRAGMENT_SHADER;
  case ShaderType::Geometry:
    return GL_GEOMETRY_SHADER;
  case ShaderType::Compute:
    return GL_COMPUTE_SHADER;
  default:
    return 0;
  }
}
} // namespace OpenGL

class Shader {
public:
  Shader() = default;

  Shader(const std::array<std::string, SHADER_TYPE_COUNT> &sources);
  ~Shader();

  u32 GetID() const { return m_ShaderProgram; }

  void Bind() const;
  void Unbind() const;

private:
  u32 m_ShaderProgram;

  u32 CreateProgram(const std::array<std::string, SHADER_TYPE_COUNT> &sources);
  u32 CompileShader(ShaderType type, const std::string &source);
};
} // namespace Renderer

namespace Assets {
namespace fs = std::filesystem;

class ShaderLoader {
public:
  static std::shared_ptr<Renderer::Shader> LoadFromFile(const fs::path &path);
};
} // namespace Assets
} // namespace Jupiter

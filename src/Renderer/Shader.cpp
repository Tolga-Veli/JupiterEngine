#include <vector>
#include <array>

#include "Shader.hpp"
#include "Core/Utils.hpp"

namespace Jupiter {
namespace Renderer {
Shader::Shader(const std::array<std::string, SHADER_TYPE_COUNT> &sources) {
  m_ShaderProgram = CreateProgram(sources);
}

Shader::~Shader() { glDeleteProgram(m_ShaderProgram); }

u32 Shader::CreateProgram(
    const std::array<std::string, SHADER_TYPE_COUNT> &stages) {
  u32 program = glCreateProgram();
  std::vector<u32> shaderIDs;
  for (u32 i = 1; i < SHADER_TYPE_COUNT; i++) {
    if (stages[i].empty())
      continue;

    u32 id = CompileShader(ShaderType{i}, stages[i]);
    if (id != 0) {
      glAttachShader(program, id);
      shaderIDs.push_back(id);
    }
  }

  glLinkProgram(program);

  i32 status = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (!status) {
    i32 length = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

    std::vector<char> info(length);
    glGetProgramInfoLog(program, length, &length, info.data());
    glDeleteProgram(program);

    J_ERROR("Shader linking Failed: {}", info.data());
    return 0;
  }

  for (auto id : shaderIDs) {
    glDetachShader(program, id);
    glDeleteShader(id);
  }

  return program;
}

u32 Shader::CompileShader(ShaderType type, const std::string &source) {
  u32 id = glCreateShader(OpenGL::GetShaderStage(ShaderType(type)));
  const char *src = source.c_str();

  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  i32 success = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    i32 length = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    std::vector<char> info(length);
    glGetShaderInfoLog(id, length, &length, info.data());

    J_ERROR("{} Shader compilation failed:\n{}", to_string(type), info.data());
    glDeleteShader(id);
    return 0;
  }

  return id;
}

void Shader::Bind() const { glUseProgram(m_ShaderProgram); }

void Shader::Unbind() const { glUseProgram(0); }
} // namespace Renderer

namespace Assets {
std::shared_ptr<Renderer::Shader>
ShaderLoader::LoadFromFile(const fs::path &path) {

  std::array<std::string, Renderer::SHADER_TYPE_COUNT> shaderSrcs;

  static auto StringToType =
      [](const std::string &type) -> Renderer::ShaderType {
    if (type == "vertex")
      return Renderer::ShaderType::Vertex;
    else if (type == "fragment")
      return Renderer::ShaderType::Fragment;
    else if (type == "geometry")
      return Renderer::ShaderType::Geometry;
    else if (type == "compute")
      return Renderer::ShaderType::Compute;
    return Renderer::ShaderType::None;
  };

  std::string source = Utils::ReadFile(path);

  std::string_view token = "#type";
  size_t pos = source.find(token, 0);
  while (pos != std::string::npos) {
    size_t eol = source.find_first_of("\r\n", pos);
    size_t beg = pos + token.length() + 1;
    std::string type = source.substr(beg, eol - beg);

    size_t nextLinePos = source.find_first_not_of("\r\n", eol);
    pos = source.find(token, nextLinePos);

    shaderSrcs[static_cast<u32>(StringToType(type))] =
        (pos == std::string::npos)
            ? source.substr(nextLinePos)
            : source.substr(nextLinePos, pos - nextLinePos);
  }
  return std::make_shared<Renderer::Shader>(shaderSrcs);
}
} // namespace Assets
} // namespace Jupiter

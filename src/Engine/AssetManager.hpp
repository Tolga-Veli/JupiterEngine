#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>
#include <string>

#include "Renderer/Texture2D.hpp"
#include "Renderer/Shader.hpp"
#include "Audio.hpp"

namespace Jupiter::Assets {
class AssetManager {
public:
  AssetManager();
  ~AssetManager();

  AssetManager(AssetManager &) = delete;
  AssetManager &operator=(AssetManager &) = delete;

  void Init();
  void Shutdown();

  AssetManager &GetInstance() { return *s_Instance; }

  static std::shared_ptr<Renderer::Texture2D>
  GetTexture2D(const std::string name);
  static std::shared_ptr<Renderer::Shader> GetShader(const std::string name);
  static std::shared_ptr<Core::Audio> GetAudio(const std::string name);

private:
  fs::path m_AssetsDir;
  static AssetManager *s_Instance;

  std::unordered_map<std::string, std::shared_ptr<Renderer::Texture2D>>
      m_Textures;
  std::unordered_map<std::string, std::shared_ptr<Renderer::Shader>> m_Shaders;
  std::unordered_map<std::string, std::shared_ptr<Core::Audio>> m_Audios;
};
}; // namespace Jupiter::Assets

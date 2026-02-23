#include "AssetManager.hpp"

namespace Jupiter::Assets {

AssetManager *AssetManager::s_Instance = nullptr;

AssetManager::AssetManager() { s_Instance = this; }
AssetManager::~AssetManager() { s_Instance = nullptr; }

void AssetManager::Init() {
  fs::path base = fs::current_path();
  if (fs::exists(base / "assets"))
    m_AssetsDir = base / "assets";
  else {
    J_ERROR("AssetManager: FAILED to find assets folder!");
    return;
  }

  J_INFO("AssetManager: Root established at {}", m_AssetsDir.string());
}

void AssetManager::Shutdown() {
  m_Textures.clear();
  m_Shaders.clear();
  m_Audios.clear();
  J_INFO("AssetManager: Resources cleared.");
}

std::shared_ptr<Renderer::Texture2D>
AssetManager::GetTexture2D(const std::string name) {
  if (!s_Instance) {
    J_ERROR("AssetManager isn't initialized");
    return nullptr;
  }

  auto &textures = s_Instance->m_Textures;
  if (textures.find(name) == textures.end()) {
    fs::path path = s_Instance->m_AssetsDir / "Textures" / name;
    textures[name] = Texture2DLoader::LoadFromFile(path);
  }
  return textures[name];
}

std::shared_ptr<Renderer::Shader>
AssetManager::GetShader(const std::string name) {
  if (!s_Instance) {
    J_ERROR("AssetManager isn't initialized");
    return nullptr;
  }

  auto &shaders = s_Instance->m_Shaders;
  if (shaders.find(name) == shaders.end()) {
    fs::path path = s_Instance->m_AssetsDir / "Shaders" / (name + ".glsl");
    shaders[name] = ShaderLoader::LoadFromFile(path);
  }
  return shaders[name];
}

std::shared_ptr<Core::Audio> AssetManager::GetAudio(const std::string name) {
  if (!s_Instance) {
    J_ERROR("AssetManager isn't initialized");
    return nullptr;
  }

  auto &audios = s_Instance->m_Audios;
  if (audios.find(name) == audios.end()) {
    fs::path path = s_Instance->m_AssetsDir / "Audio" / name;
    audios[name] = AudioLoader::LoadFromFile(path);
  }
  return audios[name];
}
} // namespace Jupiter::Assets

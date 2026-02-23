#pragma once

#include <filesystem>

namespace Jupiter {
namespace Renderer {
class Texture2D {
public:
  Texture2D(const std::filesystem::path &path);
  ~Texture2D();

private:
};
} // namespace Renderer

namespace Assets {
namespace fs = std::filesystem;

class Texture2DLoader {
public:
  static std::shared_ptr<Renderer::Texture2D>
  LoadFromFile(const fs::path &path);

private:
};

} // namespace Assets
}; // namespace Jupiter

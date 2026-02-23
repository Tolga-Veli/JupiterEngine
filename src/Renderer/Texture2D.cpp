#include "Texture2D.hpp"

#include "Core/Logging.hpp"

namespace Jupiter {
namespace Renderer {
Texture2D::Texture2D(const std::filesystem::path &path) {
  J_INFO("Tried creating a Texture2D {}", path.string());
}
Texture2D::~Texture2D() {}

}; // namespace Renderer

namespace Assets {
std::shared_ptr<Renderer::Texture2D>
Texture2DLoader::LoadFromFile(const fs::path &path) {
  J_INFO("Tried loading Texture2D: {}", path.string());
  return nullptr;
}
} // namespace Assets
}; // namespace Jupiter

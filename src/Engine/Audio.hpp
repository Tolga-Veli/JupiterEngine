#pragma once

#include <filesystem>
#include <memory>

namespace Jupiter {
namespace Core {

class Audio {
public:
  Audio(const std::filesystem::path &path);
  ~Audio();

private:
};
} // namespace Core

namespace Assets {
namespace fs = std::filesystem;
class AudioLoader {
public:
  static std::shared_ptr<Core::Audio> LoadFromFile(const fs::path &) {
    return nullptr;
  }

private:
};
}; // namespace Assets

} // namespace Jupiter

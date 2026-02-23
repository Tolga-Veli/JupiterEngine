#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <cstdint>

#include "Logging.hpp"

namespace Jupiter {
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = unsigned int;
using u64 = unsigned long long;

using i32 = int;
using i64 = long long;

namespace Utils {

inline std::string ReadFile(const std::filesystem::path &path) {
  std::ifstream in(path, std::ios::in | std::ios::binary | std::ios::ate);

  if (!in) {
    J_ERROR("Couldn't open file: {}", path.string());
    return "";
  }

  auto size = in.tellg();
  if (size <= 0)
    return "";

  std::string result;
  result.resize(size);

  in.seekg(0, std::ios::beg);
  if (!in.read(result.data(), size)) {
    J_ERROR("Couldn't load file: {}", path.string());
    return "";
  }

  return result;
}
} // namespace Utils
} // namespace Jupiter

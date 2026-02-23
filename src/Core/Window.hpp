#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Core/Utils.hpp"

namespace Jupiter::Core {
class Window {
public:
  Window(const std::string title, u32 width, u32 height);
  ~Window();

  void OnUpdate();
  bool ShouldClose() const;

  void *GetNativeWindow() const { return m_WindowHandle; }

private:
  GLFWwindow *m_WindowHandle;
  struct WindowData {
    std::string Title;
    u32 Width, Height;
  } m_Data;

  static void KeyCallback(GLFWwindow *window, i32 key, i32 scancode, i32 action,
                          i32 mode);
};
}; // namespace Jupiter::Core

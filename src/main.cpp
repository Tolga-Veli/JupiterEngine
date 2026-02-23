#include "Core/Application.hpp"

int main() {
  auto app = new Jupiter::Core::Application();
  app->Run();
  delete app;
}

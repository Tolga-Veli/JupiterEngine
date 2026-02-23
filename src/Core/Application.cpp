#include "Application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Jupiter::Core {
Application *Application::s_Instance = nullptr;

Application::Application() {
  s_Instance = this;
  m_Window = std::make_unique<Window>("Jupiter Engine", 1280, 720);
  m_AssetManager.Init();

  m_VertexBuffer = std::make_unique<Renderer::VertexBuffer>(cubeVertices);
  m_IndexBuffer = std::make_unique<Renderer::IndexBuffer>(cubeIndices);
  m_VertexArray = std::make_unique<Renderer::VertexArray>();

  Renderer::BufferLayout layout = {{"aPos", GL_FLOAT, 3, 0, false},
                                   {"aColor", GL_FLOAT, 3, 0, false}};

  m_VertexArray->SetVertexBuffer(*m_VertexBuffer, layout);
  m_VertexArray->SetIndexBuffer(*m_IndexBuffer);

  m_ShaderProgram = m_AssetManager.GetShader("basic");
  m_Running = true;
};

Application::~Application() {
  m_Running = false;
  m_AssetManager.Shutdown();
  s_Instance = nullptr;
}

void Application::Run() {
  glfwSwapInterval(1);
  glEnable(GL_DEPTH_TEST);

  while (m_Running) {
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 proj =
        glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
    glm::mat4 view =
        glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * 2.0f,
                                  glm::vec3(0.5f, 1.0f, 0.0f));
    glm::mat4 mvp = proj * view * model;

    m_ShaderProgram->Bind();
    i32 location = glGetUniformLocation(m_ShaderProgram->GetID(), "u_MVP");
    if (location != -1)
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));

    m_VertexArray->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    m_Window->OnUpdate();
    if (m_Window->ShouldClose())
      m_Running = false;
  }
}

}; // namespace Jupiter::Core

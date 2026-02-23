#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include <iostream>
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec3 aColor;\n"
                                 "out vec3 ourColor;\n"
                                 "void main() {\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   ourColor = aColor;\n"
                                 "}\0";

const char *frag_shaderSource = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "in vec3 ourColor;\n"
                                "void main() {\n"
                                "   FragColor = vec4(ourColor, 1.0f);\n"
                                "}\n\0";

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
  glfwInit();

  GLFWwindow *window = glfwCreateWindow(800, 600, "Jupiter Engine", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  glViewport(0, 0, 800, 600);

  unsigned int vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vertexShaderSource, NULL);
  glCompileShader(vert_shader);

  int success;
  char infoLog[512];
  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert_shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << '\n';
  }

  unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag_shaderSource, NULL);
  glCompileShader(frag_shader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vert_shader);
  glAttachShader(shaderProgram, frag_shader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  float vertices[] = {
      // Positions         // Colors
      0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // Top (Red)
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right (Green)
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Bottom Left (Blue)
  };
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glEnable(GL_DEPTH_TEST);

  float currentVertices[18];
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float speed = tan(glfwGetTime());
    float angle = glfwGetTime() * speed;
    float zOffset = 2.0f;
    float FOV = 1.5f;

    for (int i = 0; i < 3; i++) {
      // READ from originalVertices
      float x = vertices[i * 6];
      float y = vertices[i * 6 + 1];
      float z = vertices[i * 6 + 2];

      // Apply rotation
      float rotX = x * cos(angle) - z * sin(angle);
      float rotZ = x * sin(angle) + z * cos(angle);

      // Apply perspective
      float factor = FOV / (rotZ + zOffset);

      // WRITE to currentVertices
      currentVertices[i * 6] = rotX * factor;
      currentVertices[i * 6 + 1] = y * factor;
      currentVertices[i * 6 + 2] = rotZ;

      // Don't forget to copy the colors!
      currentVertices[i * 6 + 3] = vertices[i * 6 + 3];
      currentVertices[i * 6 + 4] = vertices[i * 6 + 4];
      currentVertices[i * 6 + 5] = vertices[i * 6 + 5];
    }

    // Push the temporary "current" array to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(currentVertices),
                    currentVertices);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  glfwTerminate();
  return 0;
}

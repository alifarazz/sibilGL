#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

#include <cstdio>

// int main(int argc, char *argv[])
int main()
{
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "test1", nullptr, nullptr); // windowed
  // GLFWwindow *window =
  //   glfwCreateWindow(800, 600, "test1", glfwGetPrimaryMonitor(), nullptr);

  glfwMakeContextCurrent(window);


  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);

  printf("%u\n", vertexBuffer);
  // while (!glfwWindowShouldClose(window))
  // {
  //   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  //     glfwSetWindowShouldClose(window, GL_TRUE);

  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }


  glDeleteBuffers(1, &vertexBuffer);

  glfwTerminate();
  return 0;
}

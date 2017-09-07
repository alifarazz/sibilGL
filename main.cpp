#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>


float vertices[] = {
   0.0f,  0.5f,
  -0.5f, -0.5,
   0.5,	 -0.5
};

std::string ReadTextFile(const char *s)
{
  std::ifstream mfile(s);
  std::string content((std::istreambuf_iterator<char>(mfile)),
		      (std::istreambuf_iterator<char>()    ));
  mfile.close();
  return content;
}

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

  GLuint vbo; // Vertex Buffer Object
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
	       sizeof(vertices),
	       vertices,
	       GL_STATIC_DRAW);

  // Read shader from source from file
  std::string vertexSoruce(ReadTextFile("./shaders/vertex.glsl"));
  // some hack, IMPROVE
  const GLchar *vertexSourceStr = vertexSoruce.c_str();
  // create shader & assign source to shader & compile
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSourceStr, NULL);
  glCompileShader(vertexShader);
  GLint status; glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  std::cout << "shader compile status" << status << ' ' << std::endl;

  //
  std::string fragmentSoruce(ReadTextFile("./shaders/fragment.glsl"));
  // IMPROVE
  const GLchar *fragmentSourceStr = fragmentSoruce.c_str();
  //
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSourceStr, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  std::cout << "fragment compile status " << status << ' ' << std::endl;


  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glBindFragDataLocation(shaderProgram, 0, "outColor");

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);


  // printf("%u\n", vertexBuffer);
  while (!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glDeleteBuffers(1, &vbo);

  glfwTerminate();
  return 0;
}

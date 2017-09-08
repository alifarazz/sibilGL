#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <chrono>
#include <cmath>


float vertices[] = {
  -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
  0.5f, 0.5f,  0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  0.5f, -0.5f, 1.0f, 1.0f, 1.0f
};

GLuint elements[] = {
  0, 1, 2,
  2, 1, 3
};

GLenum er;


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
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  // Read shader from source from file
  std::string vertexSoruce(ReadTextFile("./shaders/vertex.glsl"));
  // some hack, IMPROVE
  const GLchar *vertexSourceStr = vertexSoruce.c_str();
  // create shader & assign source to shader & compile
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSourceStr, NULL);
  glCompileShader(vertexShader);
  GLint status; glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  std::cout << "shader compile status ";
  if (status == GL_TRUE)
    std::cout << "ok."; else std::cout << status; std::cout << std::endl;

  //
  std::string fragmentSoruce(ReadTextFile("./shaders/fragment.glsl"));
  // IMPROVE
  const GLchar *fragmentSourceStr = fragmentSoruce.c_str();
  //
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSourceStr, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  std::cout << "fragment compile status ";
  if (status == GL_TRUE)
    std::cout << "ok."; else std::cout << status; std::cout << std::endl;


  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glBindFragDataLocation(shaderProgram, 0, "outColor");


  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);


  GLuint vao; // Vertex Array Object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);


  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
			5 * sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
			5 * sizeof(float), (void*)(2 * sizeof(float)));


  GLuint ebo; // Element Array Buffer Object;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


  // Main Loop
  while (!glfwWindowShouldClose(window))
  {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // glClear(GL_COLOR_BUFFER_BIT); // use???

    // Commenting glfwSwapBuffers will leave DE in a frozen state
    glfwSwapBuffers(window);
    glfwPollEvents();
  }



  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();
  return 0;
}
// er = glGetError();printf("%d\n\t%s\n", er, glGetString(er));

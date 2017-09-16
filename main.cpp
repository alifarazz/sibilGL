#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
#include <thread>

#include <SOIL/SOIL.h>
// #include <SOIL/stb_image_aug.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <chrono>
#include <cmath>


float vertices[] = {
// Position     Color             Texcoords
  -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // TOP    LEFT
   0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // TOP    RIGHT
   0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // BUTTOM RIGHT
  -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // BUTTOM LEFT
};

GLuint elements[] = {
  0, 1, 2,
  2, 3, 0
};


std::string ReadTextFile(const char *s)
{
  std::ifstream mfile(s);
  std::string content((std::istreambuf_iterator<char>(mfile)),
		      (std::istreambuf_iterator<char>()    ));
  mfile.close();
  return content;
}

static void error_callback(int error, const char *description) {
  fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

inline static void render(GLFWwindow *window) {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_ACCUM_BUFFER_BIT);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  return ;
}

// int main(int argc, char *argv[])
int main()
{
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "test1", nullptr, nullptr); // windowed
  // GLFWwindow *window =
  //   glfwCreateWindow(800, 600, "test1", glfwGetPrimaryMonitor(), nullptr);
  if (!window) {
    std::cout << "window is null" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);


  glfwSetKeyCallback(window, key_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint vbo; // Vertex Buffer Object
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


  // Read shader from source from file
  std::string vertexSoruce(ReadTextFile("./shaders/vertex.vert"));
  // some hack, IMPROVE
  const GLchar *vertexSourceStr = vertexSoruce.c_str();
  // create shader & assign source to shader & compile
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSourceStr, nullptr);
  glCompileShader(vertexShader);
  GLint status; glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  std::cout << "shader compile status ";
  if (status == GL_TRUE)
    std::cout << "ok."; else std::cout << status; std::cout << std::endl;

  //
  std::string fragmentSoruce(ReadTextFile("./shaders/fragment.frag"));
  // IMPROVE
  const GLchar *fragmentSourceStr = fragmentSoruce.c_str();
  //
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSourceStr, nullptr);
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


  GLuint tex;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);


  int width, height;
  unsigned char *image =
    SOIL_load_image("./textures/Block4.png", &width, &height, 0, SOIL_LOAD_RGB);

  if (!image)
    std::cout << "Image didn't load correctly" << std::endl;
  else {
    std::cout << "Image did load correctly  ";
    std::cout << "[" << width << ", " << height << "]" << std::endl;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
	       GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);


  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), (void*)(2 * sizeof(float)));

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
			7 * sizeof(float), (void*)(5 * sizeof(float)));


  GLuint ebo; // Element Array Buffer Object;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // int er = glGetError();printf("%d\n\t%s\n", er, glGetString(er));

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // Main Loop
  while (!glfwWindowShouldClose(window)) {

    render(window);

    // Commenting glfwSwapBuffers will leave DE in a frozen state
    glfwSwapBuffers(window);
    glfwPollEvents();
    //glfwWaitEvents();
  }

  glDeleteTextures(1, &tex);

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();
  return EXIT_SUCCESS;
}
// enum er = glGetError();printf("%d\n\t%s\n", er, glGetString(er));

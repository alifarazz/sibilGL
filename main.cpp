 #include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <thread>

// #include <SOIL/SOIL.h>
#include <FreeImage.h>
// #include <SOIL/stb_image_aug.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include <chrono>
#include <cmath>


float vertices[] = {
// X      Y      Z     R     G     B     U     V
  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

  -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

  -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

  -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
   0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
   0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

  -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // the plane
   1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
   1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
   1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
  -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
  -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
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

  GLFWwindow *window = glfwCreateWindow(800, 600, "sibil GE", nullptr, nullptr); // windowed
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
  const GLchar *vertexSourceStr = vertexSoruce.c_str();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSourceStr, nullptr);
  glCompileShader(vertexShader);
  // shader debug
  GLint status; glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  std::cout << "shader compile status ";
  if (status == GL_TRUE)
    std::cout << "ok.";
  else {
    std::cout << "not ok.\n";
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, nullptr, buffer);
    fputs(buffer, stderr);
  }
  std::cout << std::endl;


  std::string fragmentSoruce(ReadTextFile("./shaders/fragment.frag"));
  const GLchar *fragmentSourceStr = fragmentSoruce.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSourceStr, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  std::cout << "fragment compile status ";
  if (status == GL_TRUE)
    std::cout << "ok.";
  else {
    std::cout << "not ok.\n";
    char buffer[512];
    glGetShaderInfoLog(fragmentShader, 512, nullptr, buffer);
    fputs(buffer, stderr);
  }
  std::cout << std::endl;


  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glBindFragDataLocation(shaderProgram, 0, "outColor");


  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);


  GLuint vao; // Vertex Array Object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);


  GLuint textures[2];
  glGenTextures(2, textures);

  int width, height;
  FREE_IMAGE_FORMAT format;
  FIBITMAP *image;
  char *pixels;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  format = FreeImage_GetFileType("./textures/Block5.tga", 0);
  image = FreeImage_Load(format, "./textures/Block5.tga");
  image = FreeImage_ConvertTo32Bits(image);
  width = FreeImage_GetWidth(image);
  height = FreeImage_GetHeight(image);
  pixels = (char*) FreeImage_GetBits(image);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA,
	       GL_UNSIGNED_BYTE, pixels);
  FreeImage_Unload(image);
  glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  format = FreeImage_GetFileType("./textures/kitten_in_grass.png", 0);
  image = FreeImage_Load(format, "./textures/kitten_in_grass.png");
  image = FreeImage_ConvertTo32Bits(image);
  width = FreeImage_GetWidth(image);
  height = FreeImage_GetHeight(image);
  pixels = (char*) FreeImage_GetBits(image);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA,
	       GL_UNSIGNED_BYTE, pixels);
  glUniform1i(glGetUniformLocation(shaderProgram, "texDog"), 1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


  GLint uniModel = glGetUniformLocation(shaderProgram, "model");

  glm::mat4 view = glm::lookAt(glm::vec3(3.0f, 3.0f, 1.5f),
			       glm::vec3(0.0f, 0.0f, -0.5f),
			       glm::vec3(0.0f, 0.0f, 1.0f));
  GLint uniView = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

  glm::mat4 proj = glm::perspective(glm::radians(45.0f),
				    800.0f / 600.0f,
				    1.0f,
				    10.0f);
  GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));


  auto t_start = std::chrono::high_resolution_clock::now();
  GLint uniTime = glGetUniformLocation(shaderProgram, "time");

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)(3 * sizeof(float)));

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)(6 * sizeof(float)));

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // int er = glGetError();printf("%d\n\t%s\n", er, glGetString(er));

  glEnable(GL_DEPTH_TEST);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // Main Loop
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLubyte r_background = 0x4c,
	    g_background = 0x4c,
	    b_background = 0x4c;
    glClearColor(GLfloat(r_background) / 255.0f,
		 GLfloat(g_background) / 255.0f,
		 GLfloat(b_background) / 255.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);

    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
    glUniform1f(uniTime, time);

    glm::mat4 model;
    model = glm::rotate(model, time * glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 36); // draw the upper cube
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 36, 6); // draw the plane
    glDepthMask(GL_TRUE);

    // Draw the reflection of the cube in the plane
    model = glm::scale(glm::translate(model, glm::vec3(0 ,0 ,-1)),
		       glm::vec3(1, -1, 1));
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Commenting glfwSwapBuffers will leave DE in a frozen state
    glfwSwapBuffers(window);
    glfwPollEvents();
    //glfwWaitEvents();
  }

  glDeleteTextures(2, textures);

  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  glfwTerminate();
  return EXIT_SUCCESS;
}
// enum er = glGetError();printf("%d\n\t%s\n", er, glGetString(er));

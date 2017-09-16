#include <GL/glew.h>

#include <string>
#include <map>


class GLSLShader
{
public:
  GLSLShader(void);
  ~GLSLShader(void);
  void LoadFromString(GLenum whichshader, const std::string& source);
  void LoadFromFile(GLenum whichshader, const std::string& source);
  void CreateAndLinkProgram();
  void Use();
  void UnUse();
  void AddAttribute(const std::string& attribute);
  void AddUniform(const std::string& uniform);
  GLuint operator[] (const std::string& attribute);
  GLuint operator() (const std::string& uniform);
  void DeleteShaderProgram();

private:
  enum ShaderType{VERTEX_SHADER,
		  FRAGMENT_SHADER,
		  GEOMETRY_SHADER};
  GLuint _program;
  int _totalShaders;
  GLuint _shaders[3];
  std::map<std::string, GLuint> _attributeList;
  std::map<std::string, GLuint> _uniformLocationList;
};


void GLSLShader::LoadFromFile(GLenum whichshader, const std::string &source) {
  switch (whichshader) {
    case GLSLShader::VERTEX_SHADER:
      break;
  }
  return ;
}

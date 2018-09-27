#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <fstream>
#include <iostream>

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    std::string LoadShader(GLenum ShaderType);
    bool AddShader(GLenum ShaderType);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */

#ifndef SHADOW_H
#define SHADOW_H

#include "graphics_headers.h"
#include "shader.h"
#include <iostream>

using namespace std;

class Shadow
{
public:

  Shadow();
  ~Shadow();

  void Initialize();
  void Update();
  void Bind(Shader& shader);
  void Reset();

  GLuint GetDepthMap();

  void SetLightProjection(glm::mat4 lightProjection);
  void SetLightView(glm::mat4 lightView);

private:
  const unsigned int m_shadowWidth = 4096;
  const unsigned int m_shadowHeight = 4096;

  GLuint m_depthMapFBO; //the frame buffer
  GLuint m_depthMap;    //the texture

  glm::mat4 m_lightProjection = glm::mat4(1.0f);
  glm::mat4 m_lightView = glm::mat4(1.0f);

};

#endif /* SHADOW_H */
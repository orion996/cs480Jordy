#ifndef LIGHT_H
#define LIGHT_H

#include "graphics_headers.h"
#include "shader.h"
#include "shadow.h"
#include <iostream>

using namespace std;

class Light
{
public:

  Light();
  ~Light();

  void Initialize();
  void Bind(Shader& shader);
  void Reset();

  glm::mat4 GetProjection();
  glm::mat4 GetView();
  Shadow& GetShadow();

  /* public attributes to be sent to shader */

  glm::vec4 position;
  glm::vec3 focusPoint;
  //glm::vec3 direction;

  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;

  float shininess;

  bool directional;
  float angle;
  float attenuation;

  bool castsShadows;

  float x_ortho;
  float y_ortho;
  float near_plane;
  float far_plane;
  

private:

  glm::mat4 m_projection = glm::mat4(1.0);
  glm::mat4 m_view = glm::mat4(1.0);

  Shadow m_shadowMap;

};

#endif /* LIGHT_H */
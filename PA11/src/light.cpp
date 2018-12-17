#include "light.h"

Light::Light()
{
  position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  focusPoint = glm::vec3(0.0f, 0.0f, 1.0f);

  ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  specular = glm::vec4(3.0f, 3.0f, 3.0f, 3.0f);

  shininess = 50;

  directional = true;
  angle = 20.0f;
  attenuation = 0.000001f;

  castsShadows = false;
}

Light::~Light()
{

}

void Light::Initialize()
{

  if (directional)
  {
    m_projection = glm::ortho(-x_ortho, x_ortho, -y_ortho, y_ortho, near_plane, far_plane);
  }
  else
  {
    m_projection = glm::perspective(glm::radians(55.0f), 1.0f, near_plane, far_plane);
  }
  
  m_view = glm::lookAt(
    glm::vec3(
      position.x,
      position.y,
      position.z),
    focusPoint, 
    glm::vec3(1.0f, 0.0f, 0.0f));

  if (castsShadows)
  {
    m_shadowMap.Initialize();
  }
}

void Light::Bind(Shader& shader)
{
  if (castsShadows)
  {
//     cout << "light position: "
//          << position.x << ", "
//          << position.y << ", "
//          << position.z << endl;

    // Pass in the position
    glUniform3f(
      shader.GetUniformLocation("lightPosition"),
      position.x,
      position.y,
      position.z);

    // Pass in the light matrix
    glm::mat4 lightMatrix = m_projection * m_view;
    GLint lightMatrixLocation = shader.GetUniformLocation("lightSpaceMatrix");
    glUniformMatrix4fv(
    lightMatrixLocation, 
    1, 
    GL_FALSE, 
    glm::value_ptr(lightMatrix));

    //cout << "light matrix set" << endl;

    m_shadowMap.SetLightProjection(m_projection);
    m_shadowMap.SetLightView(m_view);
    m_shadowMap.Bind(shader);
  }
}

void Light::Reset()
{
  if (castsShadows)
  {
    m_shadowMap.Reset();
  }
}

glm::mat4 Light::GetProjection()
{
  return m_projection;
}

glm::mat4 Light::GetView()
{
  return m_view;
}

Shadow& Light::GetShadow()
{
  return m_shadowMap;
}
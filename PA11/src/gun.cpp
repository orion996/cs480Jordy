#include "gun.h"

Gun::Gun(string filename, float scale, glm::vec3 position) : Object(filename, scale, position)
{

}

Gun::~Gun()
{
  delete m_renderData;
  m_children.clear();
}

void Gun::Update(unsigned int dt)
{
  m_scaleMatrix = glm::scale(
    glm::mat4(1.0),
    m_scale);

  model = glm::translate(
    m_cameraTransform, 
    glm::vec3(
      1.0f * m_scale.x,
      -1.0f * m_scale.x,
      -2.0f * m_scale.x)) 
  * m_rotationMatrix 
  * m_scaleMatrix;
}

void Gun::SetCameraTransform(glm::mat4 transform)
{
  m_cameraTransform = transform;
}
#include "cross.h"

Cross::Cross(string filename, float scale, glm::vec3 position) : Object(filename, scale, position)
{

}

Cross::~Cross()
{
  delete m_renderData;
  m_children.clear();
}

void Cross::Update(unsigned int dt)
{
  model = glm::translate(
    m_cameraTransform, 
    glm::vec3(
      1.0f,
      -1.0f,
      -2.0f));
}

void Cross::SetCameraTransform(glm::mat4 transform)
{
  m_cameraTransform = transform;
}
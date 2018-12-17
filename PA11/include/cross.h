#ifndef CROSS_H
#define CROSS_H

#include "physics_object.h"

using namespace std;

class Cross : public Object
{
public:
  Cross();
  Cross(string filename);
  Cross(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Cross();

  void Update(unsigned int dt);

  void SetCameraTransform(glm::mat4 transform);

private:

  glm::mat4 m_cameraTransform;

};

#endif /* CROSS_H */

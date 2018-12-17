#ifndef GUN_H
#define GUN_H

#include "physics_object.h"

using namespace std;

class Gun : public Object
{
public:
  Gun();
  Gun(string filename);
  Gun(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Gun();

  void Update(unsigned int dt);

  void SetCameraTransform(glm::mat4 transform);

private:

  glm::mat4 m_cameraTransform;

};

#endif /* GUN_H */

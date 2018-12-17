#ifndef BB_H
#define BB_H

#include "physics_object.h"

using namespace std;

class BB : public PhysicsObject
{
public:
  BB();
  BB(string filename);
  BB(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  BB(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
  ~BB();

  bool Initialize();
  void Update(unsigned int dt);

  void SetLocalForward(glm::vec3 localForward);

private:

  bool m_justInitialized = true;

  int m_shotForce = 1;

  glm::vec3 m_localForward;

};

#endif /* BB_H */

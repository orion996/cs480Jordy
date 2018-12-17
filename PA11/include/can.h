#ifndef Can_H
#define Can_H

#include "physics_object.h"
#include "trigger_object.h"

using namespace std;

class Can : public PhysicsObject
{
public:
  Can();
  Can(string filename);
  Can(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  Can(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
  ~Can();

  bool Initialize();
  void Update(unsigned int dt);
  
  TriggerObject *m_trigger;

private:

};

#endif /* Can_H */

#ifndef LANE_H
#define LANE_H

#include "physics_object.h"

using namespace std;

class Lane : public PhysicsObject
{
public:
  Lane();
  Lane(string filename);
  Lane(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  Lane(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
  ~Lane();

  bool Initialize(btTriangleMesh *triMesh);
  void Update(unsigned int dt);

private:

};

#endif /* LANE_H */

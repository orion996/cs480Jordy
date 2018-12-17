#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "physics_object.h"

using namespace std;

class Obstacle : public PhysicsObject
{
public:
  Obstacle();
  Obstacle(string filename);
  Obstacle(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  Obstacle(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
  ~Obstacle();

  bool Initialize();
  void Update(unsigned int dt);

private:

};

#endif /* OBSTACLE_H */

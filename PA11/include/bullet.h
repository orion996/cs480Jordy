#ifndef BULLET_H
#define BULLET_H

#include "physics_object.h"

using namespace std;

class Bullet : public PhysicsObject
{
public:
  Bullet();
  Bullet(string filename);
  Bullet(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Bullet();

  bool Initialize();
  void Update(unsigned int dt);

private:

};

#endif /* BULLET_H */

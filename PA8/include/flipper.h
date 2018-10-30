#ifndef FLIPPER_H
#define FLIPPER_H

#include "physics_object.h"

using namespace std;

class Flipper : public PhysicsObject
{
public:
  Flipper();
  Flipper(string filename);
  Flipper(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Flipper();

  bool Initialize();
  void Update(unsigned int dt);

  void Flip();

  private:
};

#endif /* FLIPPER_H */

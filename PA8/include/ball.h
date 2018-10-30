#ifndef BALL_H
#define BALL_H

#include "physics_object.h"

using namespace std;

class Ball : public PhysicsObject
{
public:
  Ball();
  Ball(string filename);
  Ball(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Ball();

  bool Initialize();
  void Update(unsigned int dt);

private:

};

#endif /* BALL_H */

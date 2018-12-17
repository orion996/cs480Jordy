#ifndef LAUNCH_BARRIER_H
#define LAUNCH_BARRIER_H

#include "physics_object.h"

using namespace std;

class LaunchBarrier : public PhysicsObject
{
public:
  LaunchBarrier();
  LaunchBarrier(string filename);
  LaunchBarrier(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~LaunchBarrier();

  bool Initialize();
  void Update(unsigned int dt);

private:

};

#endif /* LAUNCH_BARRIER_H */

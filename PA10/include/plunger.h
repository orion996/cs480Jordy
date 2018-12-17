#ifndef PLUNGER_H
#define PLUNGER_H

#include "physics_object.h"

using namespace std;

class Plunger : public PhysicsObject
{
public:
  Plunger();
  Plunger(string filename);
  Plunger(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  ~Plunger();

  bool Initialize();
  void Update(unsigned int dt);

  void Pull();
  void Release();

private:
  bool m_pulling;
  bool m_releasing;

  float m_initialPosition;
  float m_thresholdPosition;
  float m_pullStep;
  float m_releaseStep;
  float m_pullDistance;
};

#endif /* PLUNGER_H */
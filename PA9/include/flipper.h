#ifndef FLIPPER_H
#define FLIPPER_H

#include "physics_object.h"

using namespace std;

class Flipper : public PhysicsObject
{
public:
  Flipper();
  Flipper(string filename);
  Flipper(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), bool left = false);
  ~Flipper();

  bool Initialize();
  void Update(unsigned int dt);

  void Flip();

private:
  bool m_left;  
  bool m_flipping;
  bool m_resetting;

  float m_initialAngle;
  float m_thresholdAngle;
  float m_currentAngle;
  float m_flipAngleStep;
  float m_resetAngleStep;

  glm::vec3 m_pivotPosition;
};

#endif /* FLIPPER_H */

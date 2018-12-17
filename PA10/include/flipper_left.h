#ifndef FLIPPER_LEFT_H
#define FLIPPER_LEFT_H

#include "physics_object.h"

using namespace std;

class FlipperLeft : public PhysicsObject
{
public:
  FlipperLeft();
  FlipperLeft(string filename);
  FlipperLeft(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  FlipperLeft(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);
  ~FlipperLeft();

  bool Initialize(btTriangleMesh *triMesh);
  void Update(unsigned int dt);

  void Flip();

private:
  bool m_flipping;
  bool m_resetting;

  float m_initialAngle;
  float m_thresholdAngle;
  float m_currentAngle;
  float m_flipAngleStep;
  float m_resetAngleStep;

  glm::vec3 m_pivotPosition;
};

#endif /* FLIPPER_LEFT_H */

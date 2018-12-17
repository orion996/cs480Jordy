#ifndef TRIGGER_OBJECT_H
#define TRIGGER_OBJECT_H

#include <btBulletDynamicsCommon.h>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "graphics_headers.h"
#include <iostream>

using namespace std;

class TriggerObject
{
public:
  TriggerObject(glm::vec3 dimensions, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  TriggerObject(glm::vec3 dimensions, glm::vec3 position, btCollisionShape* colShape);
  virtual ~TriggerObject();

  virtual bool Initialize();
  virtual void Update(unsigned int dt);
  virtual void transformTrigger(btTransform tf);

  //btCollisionShape* GetCollider();
  //btRigidBody* GetRigidBody();
  glm::vec3 GetPosition();

  btCollisionShape *m_collider;
  btMotionState *m_motionState;
  btGhostObject *m_ghostObject;

protected:
  glm::vec3 m_dimensions;
  glm::vec3 m_position;
  
};

#endif /* TRIGGER_OBJECT_H */
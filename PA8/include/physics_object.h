#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <btBulletDynamicsCommon.h>
#include "object.h"

using namespace std;

class PhysicsObject : public Object
{
public:
  PhysicsObject();
  PhysicsObject(string filename);
  PhysicsObject(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
  virtual ~PhysicsObject();

  virtual void Update(unsigned int dt);

  //btCollisionShape* GetCollider();
  //btRigidBody* GetRigidBody();

  btCollisionShape *m_collider;
  btMotionState *m_motionState;
  btRigidBody *m_rigidBody;

protected:
  
};

#endif /* PHYSICS_OBJECT_H */
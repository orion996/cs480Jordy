#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "graphics_headers.h"

using namespace std;

class Physics 
{
public:
  Physics();
  Physics(glm::vec3 gravity);
  virtual ~Physics();

  virtual bool Initialize();
  virtual void Update(unsigned int dt);
  //void AddRigidBody(btRigidBody* rigidBody);

protected:
  btBroadphaseInterface *m_broadphase;
  btCollisionDispatcher *m_dispatcher;
  btSequentialImpulseConstraintSolver *m_solver;

  btDiscreteDynamicsWorld *m_dynamicsWorld;
  glm::vec3 m_gravity;
};

#endif /* PHYSICS_H */
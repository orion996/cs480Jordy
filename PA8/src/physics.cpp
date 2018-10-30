#include "physics.h"

Physics::Physics()
{
  m_gravity = glm::vec3(0.0f, -9.81f, 0.0f);
}

Physics::Physics(glm::vec3 gravity)
{
  m_gravity = gravity;
}

Physics::~Physics()
{
  delete m_broadphase;
  m_broadphase = NULL;
  delete m_dispatcher;
  m_dispatcher = NULL;
  delete m_solver;
  m_solver = NULL;
  delete m_dynamicsWorld;
  m_dynamicsWorld = NULL;
}

bool Physics::Initialize()
{
  btDefaultCollisionConfiguration *collisionConfig;

  m_broadphase = new btDbvtBroadphase();
  collisionConfig = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(collisionConfig);
  m_solver = new btSequentialImpulseConstraintSolver();

  m_dynamicsWorld = new btDiscreteDynamicsWorld(
    m_dispatcher,
    m_broadphase,
    m_solver,
    collisionConfig);
  m_dynamicsWorld->setGravity(btVector3(
    m_gravity.x,
    m_gravity.y,
    m_gravity.z));
}

void Physics::Update(unsigned int dt)
{
  m_dynamicsWorld->stepSimulation(dt, 10);
}

/*
void Physics::AddRigidBody(btRigidBody* rigidBody)
{
  m_dynamicsWorld->addRigidBody(
    rigidBody
    );
}
*/
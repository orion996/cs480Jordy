#include "launch_barrier.h"

LaunchBarrier::LaunchBarrier() : PhysicsObject()
{

}

LaunchBarrier::LaunchBarrier(string filename) : PhysicsObject(filename)
{

}

LaunchBarrier::LaunchBarrier(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

LaunchBarrier::~LaunchBarrier()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool LaunchBarrier::Initialize()
{
  btScalar m[16];

  //set transform
  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));

  //set the scale
  m_scaleMatrix = glm::scale(
    glm::mat4(1.0),
    m_scale);

  //create the collider
  m_collider = new btBoxShape(btVector3(
    (m_scale.x) * 0.25,
    (m_scale.y) * 0.25,
    (m_scale.z) * 8.0));

  //create the motion state
  m_motionState = new btDefaultMotionState(transform);

  //set mass and inertia
  btScalar mass(0);
  btVector3 inertia(0, 0, 0);
  m_collider->calculateLocalInertia(mass, inertia);

  //set the construction info
  btRigidBody::btRigidBodyConstructionInfo ci(
    mass,
    m_motionState,
    m_collider,
    inertia
    );

  //create the rigid body
  m_rigidBody = new btRigidBody(ci);
  m_rigidBody->setActivationState(DISABLE_DEACTIVATION);

  //apply all transformations
  transform.getOpenGLMatrix(m);
  model = glm::make_mat4(m) * m_scaleMatrix;
}

void LaunchBarrier::Update(unsigned int dt)
{

}
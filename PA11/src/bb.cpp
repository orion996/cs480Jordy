#include "bb.h"

BB::BB() : PhysicsObject()
{

}

BB::BB(string filename) : PhysicsObject(filename)
{

}

BB::BB(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

BB::BB(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh) : PhysicsObject(filename, scale, position, triMesh)
{

}

BB::~BB()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool BB::Initialize()
{
  cout << "CHECK BB INITIALIZE" << endl;

  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));
  btScalar m[16];

  //set the scale
  m_scaleMatrix = glm::scale(
    glm::mat4(1.0),
    m_scale);

  //set the initial translation
  m_translationMatrix = glm::translate(
    glm::mat4(1.0f),
    m_position);

  //create the collider
  m_collider = new btBvhTriangleMeshShape(m_colliderMesh, false);

  //create the motion state
  m_motionState = new btDefaultMotionState(transform);

  //set mass and inertia
  btScalar mass(0.01f);
  btVector3 inertia(0, 0, 0);
  m_collider->calculateLocalInertia(mass, inertia);

  //set the construction info
  btRigidBody::btRigidBodyConstructionInfo ci (
    mass,
    m_motionState,
    m_collider,
    inertia
    );

  //ci.m_restitution = 1;
  //ci.m_friction = 1;
  //ci.m_rollingFriction = 0.001;

  //create the rigid body
  m_rigidBody = new btRigidBody(ci);
  m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
  m_rigidBody->setRestitution(1.0);

  model = m_translationMatrix;

  return true;
}

void BB::Update(unsigned int dt)
{
  btTransform transform;
  btScalar modelUpdate[16];

  if (m_justInitialized)
  {
    m_justInitialized = false;
    m_rigidBody->applyCentralImpulse(btVector3(
      m_localForward.x * m_shotForce,
      m_localForward.y * m_shotForce,
      m_localForward.z * m_shotForce));
  }

  //assign value to transform based on rigid body's new world status
  //then update model with transform
  m_rigidBody->getMotionState()->getWorldTransform(transform);
  m_position = glm::vec3(
    transform.getOrigin().getX(), 
    transform.getOrigin().getY(), 
    transform.getOrigin().getZ());
  
  transform.getOpenGLMatrix(modelUpdate);
  model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
}

void BB::SetLocalForward(glm::vec3 localForward)
{
  m_localForward = localForward;
}
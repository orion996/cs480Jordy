#include "plunger.h"

Plunger::Plunger() : PhysicsObject()
{

}

Plunger::Plunger(string filename) : PhysicsObject(filename)
{

}

Plunger::Plunger(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{
  m_pulling = false;
  m_releasing = false;

  m_initialPosition = position.z;
  m_thresholdPosition = m_initialPosition - 20;

  m_pullStep = 0.02f;
  m_releaseStep = 0.07f;
  m_pullDistance = 0.0f;
}

Plunger::~Plunger()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool Plunger::Initialize()
{
  cout << "CHECK PLUNGER INITIALIZE" << endl;

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
    (m_scale.x) * 0.125,
    (m_scale.y) * 0.125,
    (m_scale.z) * 0.75));

  //create the motion state
  m_motionState = new btDefaultMotionState(transform);

  //set mass and inertia
  btScalar mass(0.1f);
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
  m_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

  //apply all transformations
  transform.getOpenGLMatrix(m);
  model = glm::make_mat4(m) * m_scaleMatrix;

  cout << "FINISHED PLUNGER INITIALIZE" << endl;
}

void Plunger::Update(unsigned int dt)
{
  btTransform transform, newTransform;
  btVector3 origin, newOrigin;
  btQuaternion newRotation;
  btScalar modelUpdate[16];

  //get original origin from transform
  origin = m_rigidBody->getWorldTransform().getOrigin();

  //set position to origin
  m_position = glm::vec3(
    origin.x(),
    origin.y(),
    origin.z());

  //initialize newOrigin with current origin
  newOrigin = origin;

  if (m_pulling)
  {
    if (origin.z() > m_thresholdPosition)
    {
      m_position.z -= abs(m_pullStep * (float) (dt+1));
      m_pullDistance += abs(m_pullStep * (float) (dt+1));

    }
    else
    {
      m_position.z = m_thresholdPosition;
    }
  }
  else if (m_releasing)
  {
    if (origin.z() < m_initialPosition)
    {

      m_position.z += abs((m_releaseStep * m_pullDistance / 15) * (dt+1));
    }
    else
    {
      m_position.z = m_initialPosition;
      m_pullDistance = 0.0f;
      m_releasing = false;
    }
  }

  //set new origin
  newOrigin = btVector3(
    m_position.x,
    m_position.y,
    m_position.z);

  //set the new origin to the new transform and set world transform
  newRotation = btQuaternion::getIdentity();
  newTransform.setRotation(newRotation);
  newTransform.setOrigin(newOrigin);
  m_rigidBody->getMotionState()->setWorldTransform(newTransform);

  //get the new transform of the rigid body
  m_rigidBody->getMotionState()->getWorldTransform(transform);
  
  //apply all transformations
  transform.getOpenGLMatrix(modelUpdate);
  model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
}

void Plunger::Pull()
{
  //cout << "Pull plunger" << endl;
  if (!m_releasing)
  {
    m_pulling = true;
  }
}

void Plunger::Release()
{
  cout << "Release plunger" << endl;
  m_releasing = true;
  m_pulling = false;
}
#include "flipper.h"

Flipper::Flipper() : PhysicsObject()
{

}

Flipper::Flipper(string filename) : PhysicsObject(filename)
{

}

Flipper::Flipper(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

Flipper::~Flipper()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool Flipper::Initialize()
{
  cout << "CHECK FLIPPER INITIALIZE" << endl;

  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));
  btScalar m[16];

  m_translationMatrix = glm::translate(
    glm::mat4(1.0f),
    m_position);

  //create the collider
  m_collider = new btBoxShape(btVector3(
    m_scale.x/2,
    m_scale.y/2,
    m_scale.z/2));

  //create the motion state
  m_motionState = new btDefaultMotionState(transform);

  //set mass and inertia
  btScalar mass(0.1f);
  btVector3 inertia(0, 0, 0);
  m_collider->calculateLocalInertia(mass, inertia);

  //set the construction info
  btRigidBody::btRigidBodyConstructionInfo ci (
    mass,
    m_motionState,
    m_collider,
    inertia
    );

  //create the rigid body
  m_rigidBody = new btRigidBody(ci);
  m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
  //m_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

  model = m_translationMatrix;

  return true;
}

void Flipper::Update(unsigned int dt)
{
  btTransform transform;
  btScalar modelUpdate[16];

  //set the scale
  m_scaleMatrix = glm::scale(
    glm::mat4(1.0),
    m_scale);

  //assign value to transform based on rigid body's new world status
  //then update model with transform
  m_rigidBody->getMotionState()->getWorldTransform(transform);
  
  transform.getOpenGLMatrix(modelUpdate);
  model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
  model[3].y = 3.0f;
  
}

void Flipper::Flip()
{
  float x = 0.0f;
  float y = 0.5f;
  float z = 0.0f;
  
  //m_rigidBody->applyCentralImpulse(btVector3(.0, 0.0, 6.0));

  //m_rigidBody->applyTorqueImpulse(btVector3(x,y,z));
  //m_rigidBody->getWorldTransform()*btVector3(x,y,z);
  //m_rigidBody->applyTorqueImpulse(btVector3(x,y,z));
}

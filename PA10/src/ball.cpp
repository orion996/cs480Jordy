#include "ball.h"

Ball::Ball() : PhysicsObject()
{

}

Ball::Ball(string filename) : PhysicsObject(filename)
{

}

Ball::Ball(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

Ball::~Ball()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool Ball::Initialize()
{
  cout << "CHECK BALL INITIALIZE" << endl;
  cout << m_position.y << endl;

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
  m_collider = new btSphereShape(btScalar((m_scale.x/1.5) + 1));

  //create with correct transform info
  //create the motion state
  /*
  btDefaultMotionState *motionState = NULL;
  motionState = new btDefaultMotionState(
    btTransform(
      btQuaternion(0, 0, 0, 0),
      btVector3(0, 0, 0)));
  */
  //btDefaultMotionState *motionState = NULL;
  //motionState = new btDefaultMotionState();

  /*
  //assign this to the transform
  memset(m, '\0', 16);
  memcpy(m, &model, 16);
  transform.setFromOpenGLMatrix(m);
  */

  //set the transform
  /*
  transform.setOrigin(btVector3(
    m_position.x,
    m_position.y,
    m_position.z));
  */

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

  //don't delete motion state
  //delete motionState;
  //motionState = NULL;

  model = m_translationMatrix;

  return true;
}

void Ball::Update(unsigned int dt)
{
  btTransform transform;
  btScalar modelUpdate[16];

  //assign value to transform based on rigid body's new world status
  //then update model with transform
  m_rigidBody->getMotionState()->getWorldTransform(transform);
  m_position = glm::vec3(
    transform.getOrigin().getX(), 
    transform.getOrigin().getY(), 
    transform.getOrigin().getZ());

  if (centeringInLaunchArea)
  {
    cout << "CENTERING" << endl;

    /*
    transform.setOrigin(btVector3(
      45.5f,
      m_position.y,
      m_position.z));
    */

    m_rigidBody->translate(btVector3(
      (m_position.x - (-45.5f)) * -1,
      0,
      0));
    m_rigidBody->getMotionState()->getWorldTransform(transform);

    centeringInLaunchArea = false;
  }

  //cout << transform.getOrigin().getX() << endl;
  
  transform.getOpenGLMatrix(modelUpdate);
  model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
}

void Ball::CenterInLaunchArea()
{
  centeringInLaunchArea = true;

/*
  cout << "CENTERING" << endl;

  btScalar modelUpdate[16];
  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      -45.50000f,
      m_position.y,
      m_position.z));

  m_rigidBody->getMotionState()->setWorldTransform(transform);
  m_rigidBody->getMotionState()->getWorldTransform(transform);

  transform.getOpenGLMatrix(modelUpdate);
  model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
*/
}
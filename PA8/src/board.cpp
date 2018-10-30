#include "board.h"

Board::Board() : PhysicsObject()
{

}

Board::Board(string filename) : PhysicsObject(filename)
{

}

Board::Board(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

Board::~Board()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool Board::Initialize()
{
  cout << "CHECK BOARD INITIALIZE" << endl;

  //create the collider
  m_collider = new btStaticPlaneShape(btVector3(0.0f, 1.0f, 0.0f), 1);

  //create the motion state
  m_motionState = new btDefaultMotionState();

  //set mass and inertia
  btScalar mass(0);
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

  //don't delete motion state
  //delete motionState;
  //motionState = NULL;

  return true;
}

void Board::Update(unsigned int dt)
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
}
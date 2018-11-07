#include "world.h"
#include "graphics.h"

World::World() : Physics()
{
  moveForce = 0.5f;
}

World::World(glm::vec3 gravity) : Physics(gravity)
{
  moveForce = 0.5f;
}

World::~World()
{
  
}

bool World::Initialize()
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

  m_board = new Board("..//assets//Board.obj", 100.0f);
  m_board->Initialize();
  m_dynamicsWorld->addRigidBody(m_board->m_rigidBody);


  m_ball = new Ball("..//assets//Ball.obj", 3.0f, glm::vec3(-15.0f, 1.0f, 0.0f));
  m_ball->Initialize();  
  m_dynamicsWorld->addRigidBody(m_ball->m_rigidBody);


  m_flipperLeft = new Flipper("..//assets//Flipper.obj", 10.0f, glm::vec3(19.0f, 2.5f, -50.0f), false);
  m_flipperLeft->Initialize();
  m_dynamicsWorld->addRigidBody(m_flipperLeft->m_rigidBody);

  m_flipperRight = new Flipper("..//assets//Flipper.obj", 10.0f, glm::vec3(-19.0f, 2.5f, -50.0f), true);
  m_flipperRight->Initialize();
  m_dynamicsWorld->addRigidBody(m_flipperRight->m_rigidBody);

    m_cylinder = new Cylinder("..//assets//cylinder.obj", 10.0f, glm::vec3(0.0f, 2.0f, 25.0f));
    m_cylinder->Initialize();
    m_dynamicsWorld->addRigidBody(m_cylinder->m_rigidBody);
  
  createWalls();
  

  return true;
}

void World::Update(unsigned int dt)
{
  //cout << "entered world update function" << endl;

  m_dynamicsWorld->stepSimulation(dt, 0.5f);

  //cout << "updating objects" << endl;
  
  m_board->Update(dt);
  m_cylinder->Update(dt);
  m_ball->Update(dt);
  m_flipperRight->Update(dt);
  m_flipperLeft->Update(dt);  
  
  m_ball -> m_rigidBody -> clearForces();
  m_flipperRight -> m_rigidBody -> clearForces();



  //cout << "finished updating objects" << endl;

//   if (!flipped)
//   {
//     m_flipperRight->Flip();
//     flipped = true;
//   }
}

void World::Render(GLint& modelMatrix, char obj)
{
  /*
  switch(obj)
  {
      case 't':
          glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_board->GetModel()));
          m_board->Render();
          break;
      case 'b':
          glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
          m_ball->Render();
          break;
      case 'f':
          glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipperRight->GetModel()));
          m_flipperRight->Render();
          glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipperLeft->GetModel()));
          m_flipperLeft->Render();
          break;
      case 'c':
          glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
          m_cylinder->Render();
          break;
          
  }
  */
    
  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_board->GetModel()));
  m_board->Render();
  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
  m_ball->Render();
  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipperRight->GetModel()));
  m_flipperRight->Render();
  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_flipperLeft->GetModel()));
  m_flipperLeft->Render();
  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
  m_cylinder->Render();
}

Board& World::GetBoard()
{
  return *m_board;
}

Ball& World::GetBall()
{
  return *m_ball;
}

Flipper& World::GetFlipperRight()
{
  return *m_flipperRight;
}

Flipper& World::GetFlipperLeft()
{
  return *m_flipperLeft;
}

Cylinder& World::GetCylinder()
{
  return *m_cylinder;
}

void World::moveFlipperUp()
{
  //cout << "move flipper up" << endl;
   m_flipperRight -> m_rigidBody -> applyCentralImpulse(btVector3(0.0, 0.0, moveForce));
}

void World::moveFlipperDown()
{
  //cout << "move flipper down" << endl;
   m_flipperRight -> m_rigidBody -> applyCentralImpulse(btVector3(0.0, 0.0, moveForce * -1));

}

void World::moveFlipperRight()
{
  //cout << "move flipper right" << endl;
   m_flipperRight -> m_rigidBody -> applyCentralImpulse(btVector3(moveForce * -1, 0.0, 0.0));
}

void World::moveFlipperLeft()
{
  //cout << "move flipper left" << endl;
   m_flipperRight -> m_rigidBody -> applyCentralImpulse(btVector3(moveForce, 0.0, 0.0));
}

void World::FlipRight()
{
  m_flipperRight->Flip();
}

void World::FlipLeft()
{
  m_flipperLeft->Flip();
}

void World::createWalls()
{
  //bottom collision wall
  m_bottomWall = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
  m_bottomWallMotion = NULL;
  m_bottomWallMotion = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,0,-70)));
  btRigidBody::btRigidBodyConstructionInfo bottomCI(0, m_bottomWallMotion, m_bottomWall, btVector3(0,0,0));
  m_bottomWallRigid = new btRigidBody(bottomCI);
  m_bottomWallRigid -> setActivationState(DISABLE_DEACTIVATION);
  m_dynamicsWorld->addRigidBody(m_bottomWallRigid);
  
  //left collision wall
  m_leftWall = new btStaticPlaneShape(btVector3(-1, 0, 0), 1);
  m_leftWallMotion = NULL;
  m_leftWallMotion = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(50,0,0)));
  btRigidBody::btRigidBodyConstructionInfo leftCI(0, m_leftWallMotion, m_leftWall, btVector3(0,0,0));
  m_leftWallRigid = new btRigidBody(leftCI);
  m_leftWallRigid -> setActivationState(DISABLE_DEACTIVATION);
  m_dynamicsWorld->addRigidBody(m_leftWallRigid);
  
  //right collision wall
  m_rightWall = new btStaticPlaneShape(btVector3(1, 0, 0), 1);
  m_rightWallMotion = NULL;
  m_rightWallMotion = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(-50,0,0)));
  btRigidBody::btRigidBodyConstructionInfo rightCI(0, m_rightWallMotion, m_rightWall, btVector3(0,0,0));
  m_rightWallRigid = new btRigidBody(rightCI);
  m_rightWallRigid -> setActivationState(DISABLE_DEACTIVATION);
  m_dynamicsWorld->addRigidBody(m_rightWallRigid);
  
  //top collision wall
  m_topWall = new btStaticPlaneShape(btVector3(0, 0, -1), 1);
  m_topWallMotion = NULL;
  m_topWallMotion = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,0,90)));
  btRigidBody::btRigidBodyConstructionInfo topCI(0, m_topWallMotion, m_topWall, btVector3(0,0,0));
  m_topWallRigid = new btRigidBody(topCI);
  m_topWallRigid -> setActivationState(DISABLE_DEACTIVATION);
  m_dynamicsWorld->addRigidBody(m_topWallRigid);
  
  //collision wall to keep objects from flying out 
  m_lid = new btStaticPlaneShape(btVector3(0, -1, 0), 1);
  m_lidMotion = NULL;
  m_lidMotion = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,7,0)));
  btRigidBody::btRigidBodyConstructionInfo lidCI(0, m_lidMotion, m_lid, btVector3(0,0,0));
  m_lidRigid = new btRigidBody(lidCI);
  m_lidRigid -> setActivationState(DISABLE_DEACTIVATION);
  m_dynamicsWorld->addRigidBody(m_lidRigid);
}
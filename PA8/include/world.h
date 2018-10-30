#ifndef WORLD_H
#define WORLD_H

#include "graphics_headers.h"
#include "physics.h"
#include "board.h"
#include "ball.h"
#include "flipper.h"
#include "cylinder.h"

using namespace std;

class World : public Physics
{
public:
  World();
  World(glm::vec3 gravity);
  ~World();

  bool Initialize();
  void Update(unsigned int dt);
  void Render(GLint &modelMatrix);

  Board& GetBoard();
  Ball& GetBall();
  Flipper& GetFlipperRight();
  Cylinder& GetCylinder();

  void moveFlipperUp();
  void moveFlipperDown();
  void moveFlipperRight();
  void moveFlipperLeft();

  void createWalls();


private:
  Board *m_board;
  Ball *m_ball;
  Flipper *m_flipperRight;
  Cylinder *m_cylinder;

  bool flipped = false;

  btCollisionShape *m_bottomWall;
  btCollisionShape *m_topWall;
  btCollisionShape *m_leftWall;
  btCollisionShape *m_rightWall;
  btCollisionShape *m_lid;

  btDefaultMotionState *m_bottomWallMotion;
  btDefaultMotionState *m_topWallMotion;
  btDefaultMotionState *m_leftWallMotion;
  btDefaultMotionState *m_rightWallMotion;
  btDefaultMotionState *m_lidMotion;

  btRigidBody *m_bottomWallRigid;
  btRigidBody *m_topWallRigid;
  btRigidBody *m_leftWallRigid;
  btRigidBody *m_rightWallRigid;
  btRigidBody *m_lidRigid;
  

};

#endif /* WORLD_H */

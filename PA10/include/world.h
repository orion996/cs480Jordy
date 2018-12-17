#ifndef WORLD_H
#define WORLD_H

#include <sstream>
#include "graphics_headers.h"
#include "physics.h"
#include "board.h"
#include "ball.h"
#include "lane.h"
#include "flipper_left.h"
#include "flipper_right.h"
#include "plunger.h"
#include "cylinder.h"
#include "launch_barrier.h"
#include "trigger_object.h"
#include "bumper.h"

using namespace std;

class World : public Physics
{
public:
  World();
  World(glm::vec3 gravity);
  ~World();

  bool Initialize();
  void Update(unsigned int dt);
  void Render(GLint &modelMatrix, char obj);
  void Reset();

  void GenerateScores(string topTenList[10], bool& highScore);

  Board& GetBoard();
  Ball& GetBall();
  FlipperRight& GetFlipperRight();
  FlipperLeft& GetFlipperLeft();
  Cylinder& GetCylinder();
  int GetScore();
  int GetBallCounter();
  bool isGameOver();
  string* GetTopTenStats();
  bool IsNewHighScore();

  /*
  float GetBoardSpecular();
  float GetBallSpecular();
  float GetFlipperRightSpecular();
  float GetFlipperLeftSpecular();
  float GetCylinderSpecular();

  void SetBoardSpecular(float boardSpecular);
  void SetBallSpecular(float ballSpecular);
  void SetFlipperRightSpecular(float flipperRightSpecular);
  void SetFlipperLeftSpecular(float flipperLeftSpecular);
  void SetCylinderSpecular(float cylinderSpecular);
  */

  //flipper controls
  void moveFlipperUp();
  void moveFlipperDown();
  void moveFlipperRight();
  void moveFlipperLeft();
  void FlipRight();
  void FlipLeft();
  void PullPlunger();
  void ReleasePlunger();

  void createWalls();

private:
  Object *m_backBoard;
  Board *m_board;
  btTriangleMesh *boardMesh;
    
  btTriangleMesh *rightFlipperMesh;
  btTriangleMesh *leftFlipperMesh;

  Ball *m_ball;
  Lane *m_laneRight;
  Lane *m_laneLeft;
  btTriangleMesh *rightLaneMesh;
  btTriangleMesh *leftLaneMesh;
  FlipperRight *m_flipperRight;
  FlipperLeft *m_flipperLeft;
  Plunger *m_plunger;

  Cylinder *m_cylinder1;
  btTriangleMesh *cylMesh1;
  TriggerObject *m_cylTrigger1;
  
  Cylinder *m_cylinder2;
  btTriangleMesh *cylMesh2;
  TriggerObject *m_cylTrigger2;
  
  Cylinder *m_cylinder3;
  btTriangleMesh *cylMesh3;
  TriggerObject *m_cylTrigger3;
  
  Cylinder *m_cylinder4;
  btTriangleMesh *cylMesh4;
  TriggerObject *m_cylTrigger4;
  
  Cylinder *m_cylinder5;
  btTriangleMesh *cylMesh5;
  TriggerObject *m_cylTrigger5;

  LaunchBarrier *m_launchBarrier;
  TriggerObject *m_launchArea;

  TriggerObject *m_outArea;
  
  Bumper *m_bumperL;
  btTriangleMesh *bumpMeshL;
  Bumper *m_bumperR;
  btTriangleMesh *bumpMeshR;
  Bumper *m_bumperTL;
  btTriangleMesh *bumpMeshTL;
  Bumper *m_bumperTR;
  btTriangleMesh *bumpMeshTR;

  int m_ballCounter = 4;
  int m_dtSinceLastBallLoss = 0;

  /*
  float m_boardSpecular;
  float m_ballSpecular;
  float m_flipperRightSpecular;
  float m_flipperLeftSpecular;
  float m_cylinderSpecular;
  */

  bool m_ballInLaunchRange = true;
  bool flipped = false;
  float moveForce;

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
  
  bool m_gameOver = false;
  int m_score = 0;
  int m_scoreTimer = 0;
  ofstream m_fout;

  string m_topTenStats[10];
  bool m_newHighScore = false;
};

#endif /* WORLD_H */

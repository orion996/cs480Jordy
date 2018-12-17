#ifndef WORLD_H
#define WORLD_H


#include <sstream>
#include <btBulletDynamicsCommon.h>
#include <vector>
#include "graphics_headers.h"
#include "shader.h"
#include "light.h"
#include "physics.h"
#include "trigger_object.h"
#include "obstacle.h"
#include "gun.h"
#include "bullet.h"
#include "camera.h"
#include "bb.h"
#include "cross.h"
#include "can.h"
#include "target.h"
#include "sound.h"
#include <stdlib.h>

using namespace std;
class Sound;
class World : public Physics
{
public:
  World();
  World(glm::vec3 gravity);
  ~World();

  bool Initialize();
  void Update(unsigned int dt);
  void Render();
  void Render(Shader& shader, const vector<Light>& lights, unsigned int obj);
  void Reset();

  void PassLightingParams(Shader& shader, const vector<Light>& lights, int lightIndex, glm::vec3 lightAttr);
  void PassTargetLightingParams(Shader& shader, const vector<Light>& lights, int lightIndex, Target& target);
  void PassDefaultLighting(Shader& shader, const vector<Light>& lights, int lightIndex);

  void GenerateScores(string topTenList[10], bool& highScore);

  int GetObjectCount();
  bool isGameOver();
  int GetScore();
  bool IsNewHighScore();
  string* GetTopTenStats();
  int GetAmmoCount();
  
  void createBullet(float, float, float, float, float);
  void setCameraPos(glm::vec3 cameraPos);
  void setGameOver(bool gameOver);

  glm::mat4 m_cameraTransform;
  
  
private:
  int m_objectCount = 20;//object count
  float m_worldScale = 3;

  //ground stuff
  //Obstacle *m_ground;
  //btTriangleMesh *m_groundColMesh;
  Obstacle *m_room;
  btTriangleMesh *m_roomColMesh;
  
  double m_targetHitTimer = 0.0;
  double m_popTarget1Timer = 0.0;
  float m_popYoffset = 0.0;
  float m_popZoffset = 0.0;
  //pop-up targets
  Target *m_popTarget1;
  btTriangleMesh *m_popTarget1ColMesh;

  //target array 1; bottom
  const int m_row1Count = 8;
  Target *m_row1[8];
  btTriangleMesh *m_row1ColMesh[8];
  
  //target array 2; middle
  const int m_row2Count = 6;
  Target *m_row2[6];
  btTriangleMesh *m_row2ColMesh[6];
  
  //target array 3; top
  const int m_row3Count = 4;
  Target *m_row3[4];
  btTriangleMesh *m_row3ColMesh[4];
  
  //can
  Can *m_can;
  btTriangleMesh *m_canColMesh;
  double m_canHitTimer = 0.0f;
  bool m_canIsHit = false;
  
  //bullet stuff
  const int m_bulletInstance = 10;
  Bullet *m_bullets[10];
  int m_bulletIterator = 0;
  int m_ammoCount = 0;
  const int m_ammoMax = 100;
  
  Cross *m_cross;
  bool m_crossRender = true;

  Gun *m_gun;

  //scenery
  Obstacle *m_bar;
  btTriangleMesh *m_barColMesh;
  Obstacle *m_shelf;
  btTriangleMesh *m_shelfColMesh;
  Obstacle *m_stool1;
  Obstacle *m_stool2;
  Obstacle *m_stool3;
  btTriangleMesh *m_stool1ColMesh;
  btTriangleMesh *m_stool2ColMesh;
  btTriangleMesh *m_stool3ColMesh;
  Obstacle *m_table1;
  Obstacle *m_table2;
  btTriangleMesh *m_table1ColMesh;
  btTriangleMesh *m_table2ColMesh;
  Obstacle *m_chair1;
  Obstacle *m_chair2;
  Obstacle *m_chair3;
  btTriangleMesh *m_chair1ColMesh;
  btTriangleMesh *m_chair2ColMesh;
  btTriangleMesh *m_chair3ColMesh;

  //sky
  Object *m_sky;

  bool m_gameOver = false;
  int m_score = 0;

  bool m_newHighScore = false;
  string m_topTenStats[10];
  ofstream m_fout;
  
};

#endif /* WORLD_H */

#include "world.h"
#include "graphics.h"

World::World() : Physics()
{

}

World::World(glm::vec3 gravity) : Physics(gravity)
{

}

World::~World()
{
    
}

bool World::Initialize()
{
  //Set up the world info  
  btDefaultCollisionConfiguration *collisionConfig;
  m_broadphase = new btDbvtBroadphase();
  collisionConfig = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(collisionConfig);
  m_solver = new btSequentialImpulseConstraintSolver();

  //create the world
  m_dynamicsWorld = new btDiscreteDynamicsWorld(
    m_dispatcher,
    m_broadphase,
    m_solver,
    collisionConfig);
  m_dynamicsWorld->setGravity(btVector3(
    m_gravity.x,
    m_gravity.y,
    m_gravity.z));

  /* Initialize objects */

  //ground
  /*
  m_groundColMesh = new btTriangleMesh();
  m_ground = new Obstacle(
    "..//assets//Ground.obj",     //obj file path
    1.0f * m_worldScale,                         //scale  
    glm::vec3(0.0f, 0.0f, 0.0f) * m_worldScale,  //position 
    m_groundColMesh);             //collider mesh
  m_ground->Initialize();
  m_dynamicsWorld->addRigidBody(m_ground->m_rigidBody);
  */

  //room
  m_roomColMesh = new btTriangleMesh();
  m_room = new Obstacle(
    "..//assets//Room.obj",
    1.0 * m_worldScale,
    glm::vec3(0.0f, 0.0f, 0.0f),
    m_roomColMesh);
  m_room->Initialize();
  m_dynamicsWorld->addRigidBody(m_room->m_rigidBody);
  
  float offset = 0;
  
  //target row 1
  for(int i=0 ; i<m_row1Count ; i++)
  {
    m_row1ColMesh[i] = new btTriangleMesh();
    m_row1[i] = new Target("..//assets//TargetRed.obj", 0.55f * m_worldScale, glm::vec3(10.0f, 5.0f, (float)(-6.0 + offset))  * m_worldScale, m_row1ColMesh[i], 'r');
    m_row1[i]->Initialize();
    m_dynamicsWorld->addRigidBody(m_row1[i]->m_rigidBody);
    m_dynamicsWorld->addCollisionObject(m_row1[i]->m_trigger->m_ghostObject);
    m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    m_row1[i]->setSpeed(.04); 
    offset += 1.875;
  }
  offset = 0;
  
  //target row 2
  for(int i=0 ; i<m_row2Count ; i++)
  {
    m_row2ColMesh[i] = new btTriangleMesh();
    m_row2[i] = new Target("..//assets//TargetGreen.obj", 0.5f * m_worldScale, glm::vec3(10.0f, 7.125f, (float)(-4.0 + offset)) * m_worldScale, m_row2ColMesh[i], 'l');
    m_row2[i]->Initialize();
    m_dynamicsWorld->addRigidBody(m_row2[i]->m_rigidBody);
    m_dynamicsWorld->addCollisionObject(m_row2[i]->m_trigger->m_ghostObject);
    m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    m_row2[i]->setSpeed(.08); 
    offset += 2.5;
  }
  offset = 0;
  
  //target row 3
  for(int i=0 ; i<m_row3Count ; i++)
  {
    m_row3ColMesh[i] = new btTriangleMesh();
    m_row3[i] = new Target("..//assets//TargetBlue.obj", 0.4f * m_worldScale, glm::vec3(10.0f, 9.0f, (float)(-4.0 + offset)) * m_worldScale, m_row3ColMesh[i], 'r');
    m_row3[i]->Initialize();
    m_dynamicsWorld->addRigidBody(m_row3[i]->m_rigidBody);
    m_dynamicsWorld->addCollisionObject(m_row3[i]->m_trigger->m_ghostObject);
    m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    m_row3[i]->setSpeed(.08); 
    offset += 3.75;
  }
  offset = 0;
  
  //pop up targets
  m_popTarget1ColMesh = new btTriangleMesh();
  m_popTarget1 = new Target("..//assets//TargetPurple.obj", 0.3f * m_worldScale, glm::vec3(-900.0f, -900.0f, -900.0f) * m_worldScale, m_popTarget1ColMesh, 'r');
  m_popTarget1->Initialize();
  m_dynamicsWorld->addRigidBody(m_popTarget1->m_rigidBody);
  m_dynamicsWorld->addCollisionObject(m_popTarget1->m_trigger->m_ghostObject);
  m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
  m_popTarget1->m_isUp = false;
  
  
  //can
  m_canColMesh = new btTriangleMesh();
  m_can = new Can(
    "..//assets//Bepis.obj",
    0.2f * m_worldScale,
    glm::vec3(-10.0f, 10.0f, -15.0f), 
    m_canColMesh);
  m_can->Initialize();
  m_dynamicsWorld->addRigidBody(m_can->m_rigidBody);
  //m_dynamicsWorld->addCollisionObject(m_can->m_trigger->m_ghostObject);
  //m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
  
  //bullets
  for(int i=0 ; i<m_bulletInstance ; i++)
  {
    m_bullets[i] = new Bullet("..//assets//Bb.obj", 0.06 * m_worldScale, glm::vec3(900 *(i+1), -900*(i+1), -900*(i+1)));
    m_bullets[i]->Initialize();
    m_dynamicsWorld->addRigidBody(m_bullets[i]->m_rigidBody);
  }
  
  //camera objects
  m_gun = new Gun("..//assets//Gun.obj", 1.0 * m_worldScale);
  m_gun->SetRotation(M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
  m_cross = new Cross("..//assets//cross.obj", 1.0 * m_worldScale);

  /* scenery */

  //bar
  m_barColMesh = new btTriangleMesh();
  m_bar = new Obstacle(
    "..//assets//bar.obj",
    m_worldScale,
    glm::vec3(10.0f, -0.5f, 0.0f),
    m_barColMesh);
  m_bar->SetRotation(M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
  m_bar->Initialize();
  m_dynamicsWorld->addRigidBody(m_bar->m_rigidBody);

  //shelf
  m_shelfColMesh = new btTriangleMesh();
  m_shelf = new Obstacle(
    "..//assets//Shelf.obj",
    m_worldScale,
    glm::vec3(40.0f, 13.5f, 0.0f),
    m_shelfColMesh);
  m_shelf->SetRotation(M_PI, glm::vec3(0.0f, 1.0f, 0.0f));
  m_shelf->Initialize();
  m_dynamicsWorld->addRigidBody(m_shelf->m_rigidBody);

  //stools
  m_stool1ColMesh = new btTriangleMesh();
  m_stool1 = new Obstacle(
    "..//assets//Stool.obj",
    m_worldScale * 1.4,
    glm::vec3(-2.0f, -6.0f, -18.0f),
    m_stool1ColMesh);
  m_stool1->Initialize();
  m_dynamicsWorld->addRigidBody(m_stool1->m_rigidBody);

  m_stool2ColMesh = new btTriangleMesh();
  m_stool2 = new Obstacle(
    "..//assets//Stool.obj",
    m_worldScale * 1.4,
    glm::vec3(-2.0f, -6.0f, 0.0f),
    m_stool2ColMesh);
  m_stool2->Initialize();
  m_dynamicsWorld->addRigidBody(m_stool2->m_rigidBody);

  m_stool3ColMesh = new btTriangleMesh();
  m_stool3 = new Obstacle(
    "..//assets//Stool.obj",
    m_worldScale * 1.4,
    glm::vec3(-2.0f, -6.0f, 18.0f),
    m_stool3ColMesh);
  m_stool3->Initialize();
  m_dynamicsWorld->addRigidBody(m_stool3->m_rigidBody);

  //tables
  m_table1ColMesh = new btTriangleMesh();
  m_table1 = new Obstacle(
    "..//assets//Table.obj",
    m_worldScale,
    glm::vec3(-15.0f, -6.0f, -17.0f),
    m_table1ColMesh);
  m_table1->Initialize();
  m_dynamicsWorld->addRigidBody(m_table1->m_rigidBody);

  m_table2ColMesh = new btTriangleMesh();
  m_table2 = new Obstacle(
    "..//assets//Table.obj",
    m_worldScale,
    glm::vec3(-15.0f, -6.0f, 17.0f),
    m_table2ColMesh);
  m_table2->Initialize();
  m_dynamicsWorld->addRigidBody(m_table2->m_rigidBody);

  //chairs
  float chairScale = 0.85f;
  m_chair1ColMesh = new btTriangleMesh();
  m_chair1 = new Obstacle(
    "..//assets//Chair.obj",
    chairScale * m_worldScale,
    glm::vec3(-15.0f, 2, -35.0f),
    m_chair1ColMesh);
  m_chair1->Initialize();
  m_dynamicsWorld->addRigidBody(m_chair1->m_rigidBody);

  m_chair2ColMesh = new btTriangleMesh();
  m_chair2 = new Obstacle(
    "..//assets//Chair.obj",
    chairScale * m_worldScale,
    glm::vec3(-5.0f, 2, 35.0f),
    m_chair2ColMesh);
  m_chair2->SetRotation(7*M_PI/6, glm::vec3(0.0f, 1.0f, 0.0f));
  m_chair2->Initialize();
  m_dynamicsWorld->addRigidBody(m_chair2->m_rigidBody);

  m_chair3ColMesh = new btTriangleMesh();
  m_chair3 = new Obstacle(
    "..//assets//Chair.obj",
    chairScale * m_worldScale,
    glm::vec3(-30.0f, 2, 30.0f),
    m_chair3ColMesh);
  m_chair3->SetRotation(3*M_PI/4, glm::vec3(0.0f, 1.0f, 0.0f));
  m_chair3->Initialize();
  m_dynamicsWorld->addRigidBody(m_chair3->m_rigidBody);

  //sky
  m_sky = new Object(
    "..//assets//Sky.obj",
    20.0);
  
  return true;
}

void World::Update(unsigned int dt)
{
  m_dynamicsWorld->stepSimulation(dt, 0.05f);

  m_gun->SetCameraTransform(m_cameraTransform);
  m_cross->SetCameraTransform(m_cameraTransform);

  m_room->Update(dt);
  m_bar->Update(dt);
  m_shelf->Update(dt);
  m_stool1->Update(dt);
  m_stool2->Update(dt);
  m_stool3->Update(dt);
  m_table1->Update(dt);
  m_table2->Update(dt);
  m_chair1->Update(dt);
  m_chair2->Update(dt);
  m_chair3->Update(dt);
  m_sky->Update(dt);
  
  for(int i=0 ; i<m_row1Count ; i++)
    m_row1[i]->rowUpdate(dt);

  
  for(int i=0 ; i<m_row2Count ; i++)
    m_row2[i]->rowUpdate(dt);
  
  for(int i=0 ; i<m_row3Count ; i++)
    m_row3[i]->rowUpdate(dt);
  
  if(!m_popTarget1->m_isUp)
  {
    m_popYoffset = rand() % 8;
    m_popZoffset = rand() % 5;
  }
  
  m_popTarget1->popUpdate(dt, (glm::vec3(8.0f, 4.0f + m_popYoffset, -0.0f + m_popZoffset)) * m_worldScale);
  
  m_gun->Update(dt);
  if(m_crossRender) m_cross->Update(dt);
  m_can->Update(dt);
  
  for(int i=0 ; i<m_bulletInstance ; i++)
  {
    m_bullets[i]->Update(dt);
  }
  
  //check for popup target
  m_popTarget1Timer += dt;
  if(m_popTarget1Timer > 5000)
      m_popTarget1->m_isUp = true;
  
  
  //------------------------------------------------
  
  //increase timers by dt
  m_targetHitTimer += dt;
  
  //create bool
  bool ifTargetHit50 = false;
  bool ifTargetHit100 = false;
  bool ifTargetHit250 = false;
  bool ifTargetHit500 = false;

  //get number over overlaps
//   int canCollisionNum = m_can->m_trigger->m_ghostObject->getNumOverlappingObjects();
  int row1CollisionNum[m_row1Count];
  for(int n=0 ; n<m_row1Count ; n++)
      row1CollisionNum[n] = m_row1[n]->m_trigger->m_ghostObject->getNumOverlappingObjects();
  int row2CollisionNum[m_row2Count];
  for(int n=0 ; n<m_row2Count ; n++)
      row2CollisionNum[n] = m_row2[n]->m_trigger->m_ghostObject->getNumOverlappingObjects();
  int row3CollisionNum[m_row3Count];
  for(int n=0 ; n<m_row3Count ; n++)
      row3CollisionNum[n] = m_row3[n]->m_trigger->m_ghostObject->getNumOverlappingObjects();
  
  int popTarget1CollisionNum = m_popTarget1->m_trigger->m_ghostObject->getNumOverlappingObjects(); 
  
  for(int n=0 ; n<m_row1Count ; n++)
  {
    for(int i=0 ; i<row1CollisionNum[n] ; i++)
    {
        btRigidBody *collidingBody = dynamic_cast<btRigidBody*>(m_row1[n]->m_trigger->m_ghostObject->getOverlappingObject(i));
        
        for(int j=0 ; j<m_bulletIterator ; j++)
        {
            if(collidingBody->getCompanionId() == m_bullets[j]->m_rigidBody->getCompanionId())
            {
                if(m_row1[n]->m_isUp)
                    ifTargetHit50 = true;
                
                m_row1[n]->m_isUp = false;
            }
        }
    }
  }
  
  for(int n=0 ; n<m_row2Count ; n++)
  {
    for(int i=0 ; i<row2CollisionNum[n] ; i++)
    {
        btRigidBody *collidingBody = dynamic_cast<btRigidBody*>(m_row2[n]->m_trigger->m_ghostObject->getOverlappingObject(i));
        
        for(int j=0 ; j<m_bulletIterator ; j++)
        {
            if(collidingBody->getCompanionId() == m_bullets[j]->m_rigidBody->getCompanionId())
            {
                if(m_row2[n]->m_isUp)
                    ifTargetHit100 = true;
                
                m_row2[n]->m_isUp = false;
            }
        }
    }
  }
  
  for(int n=0 ; n<m_row3Count ; n++)
  {
    for(int i=0 ; i<row3CollisionNum[n] ; i++)
    {
        btRigidBody *collidingBody = dynamic_cast<btRigidBody*>(m_row3[n]->m_trigger->m_ghostObject->getOverlappingObject(i));
        
        for(int j=0 ; j<m_bulletIterator ; j++)
        {
            if(collidingBody->getCompanionId() == m_bullets[j]->m_rigidBody->getCompanionId())
            {
                if(m_row3[n]->m_isUp)
                    ifTargetHit250 = true;
                
                m_row3[n]->m_isUp = false;
            }
        }
    }
  }
  for(int i=0 ; i<popTarget1CollisionNum ; i++)
  {
    btRigidBody *collidingBody = dynamic_cast<btRigidBody*>(m_popTarget1->m_trigger->m_ghostObject->getOverlappingObject(i));
        
    for(int j=0 ; j<m_bulletIterator ; j++)
    {
        if(collidingBody->getCompanionId() == m_bullets[j]->m_rigidBody->getCompanionId())
        {
            if(m_popTarget1->m_isUp)
                ifTargetHit500 = true;
            
            m_popTarget1->m_isUp = false;
        }
    }
  }
  
  
  //do stuff
  if(ifTargetHit50 && m_targetHitTimer > 200) /**PLAY A "BTINNNNNNNG" SOUND**/
  {
      cout << "HIT TARGET" << endl;
      Mix_PlayChannel(-1, Sound::soundEffect, 0);
      m_score += 50;
      m_targetHitTimer = 0.0;
  }
  if(ifTargetHit100 && m_targetHitTimer > 200) /**PLAY A "BTINNNNNNNG" SOUND**/
  {
      cout << "HIT TARGET" << endl;
      Mix_PlayChannel(-1, Sound::soundEffect, 0);
      m_score += 100;
      m_targetHitTimer = 0.0;
  }
  if(ifTargetHit250 && m_targetHitTimer > 200) /**PLAY A "BTINNNNNNNG" SOUND**/
  {
      cout << "HIT TARGET" << endl;
      Mix_PlayChannel(-1, Sound::soundEffect, 0);
      m_score += 250;
      m_targetHitTimer = 0.0;
  }
  if(ifTargetHit500 && m_targetHitTimer > 200) /**PLAY A "BTINNNNNNNG" SOUND**/
  {
      cout << "HIT TARGET" << endl;
      Mix_PlayChannel(-1, Sound::soundEffect, 0);
      m_score += 500;
      m_targetHitTimer = 0.0;
      m_popTarget1Timer = 0.0;
  }
}


void World::Render()
{
  /* render all generic renderable objects */
}

void World::Render(Shader& shader, const vector<Light>& lights, unsigned int obj)
{
  /* render select objects */

  //objects that are rendered in this function should not 
  //be rendered in the other render function

  GLint modelMatrix = shader.GetUniformLocation("modelMatrix");

  switch(obj)
  {
    case 0:
      //render specific object with id 0
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_room->GetModel()));
      m_room->Render();
      break;
    case 1:
        for(int i=0 ; i<m_row1Count ; i++)
        {
            PassTargetLightingParams(shader, lights, 2, *m_row1[i]);
            glUniformMatrix4fv(
                modelMatrix, 
                1, 
                GL_FALSE, 
                glm::value_ptr(m_row1[i]->GetModel()));
            m_row1[i]->Render();
        }
        
        for(int i=0 ; i<m_row2Count ; i++)
        {
            PassTargetLightingParams(shader, lights, 2, *m_row2[i]);
            glUniformMatrix4fv(
                modelMatrix, 
                1, 
                GL_FALSE, 
                glm::value_ptr(m_row2[i]->GetModel()));
            m_row2[i]->Render();
        }
        
        for(int i=0 ; i<m_row3Count ; i++)
        {
            PassTargetLightingParams(shader, lights, 2, *m_row3[i]);
            glUniformMatrix4fv(
                modelMatrix, 
                1, 
                GL_FALSE, 
                glm::value_ptr(m_row3[i]->GetModel()));
            m_row3[i]->Render();
        }
        PassDefaultLighting(shader, lights, 2);
        
        glUniformMatrix4fv(
            modelMatrix, 
            1, 
            GL_FALSE, 
            glm::value_ptr(m_popTarget1->GetModel()));
        m_popTarget1->Render();
      break;
    case 2:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_gun->GetModel()));
      m_gun->Render();
      
      if(m_crossRender)
      {
        glUniformMatrix4fv(
            modelMatrix, 
            1, 
            GL_FALSE, 
            glm::value_ptr(m_cross->GetModel()));
        m_cross->Render();
      }
      break;
    case 3:
        for(int i=0 ; i<m_bulletInstance ; i++)
        {
            glUniformMatrix4fv(
                modelMatrix, 
                1, 
                GL_FALSE, 
                glm::value_ptr(m_bullets[i]->GetModel()));
            m_bullets[i]->Render();
        }
      break;
    case 4:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_bar->GetModel()));
      m_bar->Render();
      break;
    case 5:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_shelf->GetModel()));
      m_shelf->Render();
      break;
    case 6:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_stool1->GetModel()));
      m_stool1->Render();
      break;
    case 7:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_stool2->GetModel()));
      m_stool2->Render();
      break;
    case 8:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_stool3->GetModel()));
      m_stool3->Render();
      break;
    case 9:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_table1->GetModel()));
      m_table1->Render();
      break;
    case 10:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_table2->GetModel()));
      m_table2->Render();
      break;
    case 11:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_chair1->GetModel()));
      m_chair1->Render();
      break;
    case 12:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_chair2->GetModel()));
      m_chair2->Render();
      break;
    case 13:
      glUniformMatrix4fv(
        modelMatrix, 
        1, 
        GL_FALSE, 
        glm::value_ptr(m_chair3->GetModel()));
      m_chair3->Render();
    case 14:
      glUniformMatrix4fv(
        modelMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(m_can->GetModel()));
      m_can->Render();
      break;
    case 15:
      PassLightingParams(shader, lights, 1, glm::vec3(0.15f));
      glUniformMatrix4fv(
        modelMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(m_sky->GetModel()));
      m_sky->Render();
      PassDefaultLighting(shader, lights, 1);
    //add more cases for more objects
    default: break;
  }
}

void World::Reset()
{
  m_gameOver = false;

  //reset game stats
  m_score = 0;
  m_crossRender = true;
  m_ammoCount = 0;
  m_newHighScore = false;
}

void World::PassLightingParams(Shader& shader, const vector<Light>& lights, int lightIndex, glm::vec3 lightAttr)
{
  string lightArray = "lights[" + to_string(lightIndex) + "]";
  string variableName = lightArray + ".ambientProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].ambient.x * lightAttr.x, 
    lights[lightIndex].ambient.y * lightAttr.y, 
    lights[lightIndex].ambient.z * lightAttr.z, 
    lights[lightIndex].ambient.w);
  variableName = lightArray + ".specularProduct";
  variableName = lightArray + ".diffuseProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].diffuse.x * lightAttr.x, 
    lights[lightIndex].diffuse.y * lightAttr.y, 
    lights[lightIndex].diffuse.z * lightAttr.z, 
    lights[lightIndex].diffuse.w);
  variableName = lightArray + ".specularProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].specular.x * lightAttr.x, 
    lights[lightIndex].specular.y * lightAttr.y, 
    lights[lightIndex].specular.z * lightAttr.z, 
    lights[lightIndex].specular.w);
}

void World::PassTargetLightingParams(Shader& shader, const vector<Light>& lights, int lightIndex, Target& target)
{
  string lightArray = "lights[" + to_string(lightIndex) + "]";
  string variableName = lightArray + ".ambientProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].ambient.x + target.m_ambient.x, 
    lights[lightIndex].ambient.y + target.m_ambient.y, 
    lights[lightIndex].ambient.z + target.m_ambient.z, 
    lights[lightIndex].ambient.w);
  variableName = lightArray + ".specularProduct";
  variableName = lightArray + ".diffuseProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].diffuse.x + target.m_diffuse.x, 
    lights[lightIndex].diffuse.y + target.m_diffuse.y, 
    lights[lightIndex].diffuse.z + target.m_diffuse.z, 
    lights[lightIndex].diffuse.w);
  variableName = lightArray + ".specularProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].specular.x + target.m_specular.x, 
    lights[lightIndex].specular.y + target.m_specular.y, 
    lights[lightIndex].specular.z + target.m_specular.z, 
    lights[lightIndex].specular.w);
}

void World::PassDefaultLighting(Shader& shader, const vector<Light>& lights, int lightIndex)
{
  string lightArray = "lights[" + to_string(lightIndex) + "]";
  string variableName = lightArray + ".ambientProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].ambient.x, 
    lights[lightIndex].ambient.y, 
    lights[lightIndex].ambient.z, 
    lights[lightIndex].ambient.w);
  variableName = lightArray + ".diffuseProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].diffuse.x, 
    lights[lightIndex].diffuse.y, 
    lights[lightIndex].diffuse.z, 
    lights[lightIndex].diffuse.w);
  variableName = lightArray + ".specularProduct";
  glUniform4f(shader.GetUniformLocation(variableName.c_str()),
    lights[lightIndex].specular.x, 
    lights[lightIndex].specular.y, 
    lights[lightIndex].specular.z, 
    lights[lightIndex].specular.w);
}

void World::GenerateScores(string topTenList[10], bool& highScore)
{
    ifstream fin, topFin;
    topFin.open("..//assets//topScores.txt");
    
    struct TopPlayer
    {
      int score;
      string name;
    };
    
    TopPlayer leaderBoard[11];
    
    cout << endl << "YOUR SCORE: " << m_score << endl;
    
    for(int i=0 ; i<10 ; i++)
    {
       topFin >> leaderBoard[i].score >> leaderBoard[i].name;
       //cout << leaderBoard[i].score << " " << leaderBoard[i].name << endl;
    }

    //cout << m_score << ", " << leaderBoard[0].score << endl;
    if (m_score > leaderBoard[0].score)
    {
      highScore = true;
    }

    string str;
    ifstream nameFin;
    nameFin.open("..//assets//nameLog.txt");
    nameFin >> str;
    nameFin.close();
    

    leaderBoard[10].score = m_score;
    leaderBoard[10].name = str;

    
    //topScores.push_back(score);
    
    topFin.close();
    ofstream fout;
    fout.open("..//assets//topScores.txt");

    //**SORT**

    TopPlayer temp;
    for(int i=0 ; i<11 ; i++)
    {
      for(int j=i+1 ; j<11 ; j++)
      {
        if(leaderBoard[i].score < leaderBoard[j].score)
        {
          //swap
          temp = leaderBoard[i];
          leaderBoard[i] = leaderBoard[j];
          leaderBoard[j] = temp;
        }
      }
    }

    //********
    
    int rank = 1;
    cout << endl << "**TOP SCORES**" << endl;
    for(int i=0; i<10 ; i++)
    {
        stringstream ss;
        ss << rank++ << ") " << leaderBoard[i].score << " " << leaderBoard[i].name;
        cout << ss.str() << endl;
        topTenList[i] = ss.str();
        fout << leaderBoard[i].score << " " << leaderBoard[i].name << endl; 
    }
        
    fout.close();
}

int World::GetObjectCount()
{
  return m_objectCount;
}

bool World::isGameOver()
{
  return m_gameOver;
}

int World::GetScore()
{
  return m_score;
}

bool World::IsNewHighScore()
{
  return m_newHighScore;
}

string* World::GetTopTenStats()
{
  return m_topTenStats;
}

void World::createBullet(float x, float y, float z, float pitch, float yaw)
{
    m_ammoCount++;
    if(m_ammoCount > m_ammoMax) /**PLAY A CLICK SOUND**/
    {
        cout << "Ran out of Ammo!!" << endl;
        
        //end the game
        //m_score = 0;
        setGameOver(true);
    }
    
    else /**shoot a bullet;PLAY AN AIR RIFLE POP SOUND**/
    {
        if(m_bulletIterator >= m_bulletInstance)
        m_bulletIterator = 0;
        
        glm::vec3 localForward = glm::vec3(0.0, 0.0, -1.0);
        localForward.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        localForward.y = sin(glm::radians(pitch));
        localForward.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        localForward = glm::normalize(localForward);
        btVector3 shootDir = btVector3(localForward.x,localForward.y,localForward.z);
        //m_bulletDir[m_bulletIterator] = btVector3(localForward.x,localForward.y,localForward.z);
        
        cout << "BULLET POSITION: " << x << " " << y << " "  << z << endl;
        cout << "LOOKING AT: " << localForward.x << " " << localForward.y << " " << localForward.z << endl;
        
        btTransform bulletTransform(btQuaternion::getIdentity(), btVector3(x, y, z));

        //make bullet shoot from camera location
        m_bullets[m_bulletIterator]->m_rigidBody->setWorldTransform(bulletTransform);
        m_bullets[m_bulletIterator]->m_rigidBody->setLinearVelocity(btVector3(0,0,0));
        m_bullets[m_bulletIterator]->m_rigidBody->setLinearVelocity(shootDir * .1 * m_worldScale);
        m_bulletIterator++;
        Mix_PlayChannel(-1, Sound::soundEffect2, 0);
    }
}

int World::GetAmmoCount()
{
    if(m_ammoMax - m_ammoCount > 0)
        return m_ammoMax - m_ammoCount;
    
    else
        return 0;
}

void World::setGameOver(bool gameOver)
{
  if (gameOver)
  {
    GenerateScores(m_topTenStats, m_newHighScore);
    m_gameOver = true;
    m_crossRender = false;
  }
  else
  {
    Reset();
  }
}
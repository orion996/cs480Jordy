#include "target.h"

Target::Target() : PhysicsObject()
{
    m_direction = 'r';
    m_speedMod = .06;
}

Target::Target(string filename) : PhysicsObject(filename)
{
    m_direction = 'r';
    m_speedMod = .06;
}

Target::Target(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{
    m_direction = 'r';
    m_speedMod = .06;
}

Target::Target(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh, char dir) : PhysicsObject(filename, scale, position, triMesh)
{
    m_direction = dir;
    m_speedMod = .06;
}

Target::~Target()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}


bool Target::Initialize()
{
  cout << "CHECK Target INITIALIZE" << endl;

  //set transform
  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));

  //create the collider
  m_collider = new btBvhTriangleMeshShape(m_colliderMesh, false);

  //create the motion state
  m_motionState = new btDefaultMotionState(transform);

  //set mass and inertia
  btScalar mass(0.0f);
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
  m_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
  
  //Initialize Trigger  
  m_trigger = new TriggerObject(
      glm::vec3(0.00001, 0.00001, 0.00001) * m_scale,
      glm::vec3(m_position.x, m_position.y, m_position.z)
  );
  m_trigger->Initialize();
  
  model = m_translationMatrix;

  return true;
}

void Target::rowUpdate(unsigned int dt)
{
    btTransform transform, newTransform;
    btScalar modelUpdate[16];
    btVector3 origin = m_rigidBody->getWorldTransform().getOrigin();
    btMatrix3x3 basis = m_rigidBody->getWorldTransform().getBasis();
    
    if(m_isUp)
    {
        m_position = glm::vec3(origin.x(), origin.y(), origin.z());

        if(m_direction == 'u')
            m_position.y += m_speedMod * (dt + 1) * 0.1f;
        else if(m_direction == 'l')
            m_position.z -= m_speedMod * (dt + 1) * 0.1f;
        else if(m_direction == 'd')
            m_position.y -= m_speedMod * (dt + 1) * 0.1f;
        else if(m_direction == 'r')
            m_position.z += m_speedMod * (dt + 1) * 0.1f;
        
        m_ambient = glm::vec3(0.0, 0.0, 0.0);
        m_diffuse = glm::vec3(0.0, 0.0, 0.0);
        m_specular = glm::vec3(0.0, 0.0, 0.0); 
        
        if(m_position.z >= 22.5 && m_direction == 'r')
            m_position = glm::vec3(origin.x(), origin.y(), -22.5f);
        
        if(m_position.z <= -22.5 && m_direction == 'l')
            m_position = glm::vec3(origin.x(), origin.y(), 22.5f);
        
        //translate the collision box
        btVector3 newOrigin = btVector3(m_position.x, m_position.y, m_position.z);
        newTransform.setOrigin(newOrigin);
        
        basis.setRotation(btQuaternion(
            0,
            0,
            0
        ));
        newTransform.setBasis(basis);
        
        m_rigidBody->getMotionState()->setWorldTransform(newTransform);
        
        //translate the trigger
        m_trigger->transformTrigger(newTransform);
        /*
        glm::vec3 trigPos = m_trigger->GetPosition();
        cout << "Trigger Position: "
             << "("
             << trigPos.x << ", "
             << trigPos.y << ", "
             << trigPos.z << ")"
             << endl;
        */

        //set the scale
        m_scaleMatrix = glm::scale(
                glm::mat4(1.0),
                m_scale);

        //assign value to transform based on rigid body's new world status
        //then update model with transform
        m_rigidBody->getMotionState()->getWorldTransform(transform);
        newTransform.getOpenGLMatrix(modelUpdate);
        model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
    }
    else
    {
        m_position = glm::vec3(origin.x(), origin.y(), origin.z());
        
        if(m_direction == 'u')
            m_position.y += m_speedMod * (dt + 1) * 0.1f;
        else if(m_direction == 'l')
            m_position.z -= m_speedMod * (dt + 1) * 0.1f;
        else if(m_direction == 'd')
            m_position.y -= m_speedMod * (dt + 1) * 0.1f;
        else if(m_direction == 'r')
            m_position.z += m_speedMod * (dt + 1) * 0.1f;

        m_ambient = glm::vec3(20.0, 20.0, 20.0);
        //m_diffuse = glm::vec3(20.0, 20.0, 20.0); 
        //m_specular = glm::vec3(20.0, 20.0, 20.0);        
        
        if(m_position.z >= 22.5 && m_direction == 'r')
        {
            m_position = glm::vec3(origin.x(), origin.y(), -22.5f);
            m_isUp = true;
        }
        
        if(m_position.z <= -22.5 && m_direction == 'l')
        {
            m_position = glm::vec3(origin.x(), origin.y(), 22.5f);
            m_isUp = true;
        }
        
        //translate the collision box
        btVector3 newOrigin = btVector3(m_position.x, m_position.y, m_position.z);
        
        newTransform.setOrigin(newOrigin);
        
      basis.setRotation(btQuaternion(
        0,
        0,
        (M_PI/2)
      ));
        newTransform.setBasis(basis);
        
        m_rigidBody->getMotionState()->setWorldTransform(newTransform);
        
        //translate the trigger
        m_trigger->transformTrigger(newTransform);

        //set the scale
        m_scaleMatrix = glm::scale(
                glm::mat4(1.0),
                m_scale);

        //assign value to transform based on rigid body's new world status
        //then update model with transform
        m_rigidBody->getMotionState()->getWorldTransform(transform);
        newTransform.getOpenGLMatrix(modelUpdate);
        model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
    }
}

void Target::setSpeed(float mod)
{
    m_speedMod = mod;
}

void Target::popUpdate(unsigned int dt, glm::vec3 pos)
{
    btTransform transform, newTransform;
    btScalar modelUpdate[16];
    btVector3 origin = m_rigidBody->getWorldTransform().getOrigin();
    btMatrix3x3 basis = m_rigidBody->getWorldTransform().getBasis();
    
    if(m_isUp)
    {
        btTransform transform, newTransform;
        btScalar modelUpdate[16];
        btVector3 origin = m_rigidBody->getWorldTransform().getOrigin();
        btMatrix3x3 basis = m_rigidBody->getWorldTransform().getBasis();
        
        m_position = pos;
        
        btVector3 newOrigin = btVector3(m_position.x, m_position.y, m_position.z);
        
        newTransform.setOrigin(newOrigin);
        
        
        basis.setRotation(btQuaternion(
            0,
            0,
            0
        ));
        
        newTransform.setBasis(basis);
        
        m_rigidBody->getMotionState()->setWorldTransform(newTransform);
        
        //translate the trigger
        m_trigger->transformTrigger(newTransform);

        //set the scale
        m_scaleMatrix = glm::scale(
                glm::mat4(1.0),
                m_scale);

        //assign value to transform based on rigid body's new world status
        //then update model with transform
        m_rigidBody->getMotionState()->getWorldTransform(transform);
        newTransform.getOpenGLMatrix(modelUpdate);
        model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
    }
    else
    {
        btTransform transform, newTransform;
        btScalar modelUpdate[16];
        btVector3 origin = m_rigidBody->getWorldTransform().getOrigin();
        btMatrix3x3 basis = m_rigidBody->getWorldTransform().getBasis();
        
        m_position = glm::vec3(-900.0f, -900.0f, -900.0f);
        
        btVector3 newOrigin = btVector3(m_position.x, m_position.y, m_position.z);
        
        newTransform.setOrigin(newOrigin);
        
        
        basis.setRotation(btQuaternion(
            0,
            0,
            0
        ));
        
        newTransform.setBasis(basis);
        
        m_rigidBody->getMotionState()->setWorldTransform(newTransform);
        
        //translate the trigger
        m_trigger->transformTrigger(newTransform);
        glm::vec3 trigPos = m_trigger->GetPosition();
        /*
        cout << "Trigger Position: "
             << "("
             << trigPos.x << ", "
             << trigPos.y << ", "
             << trigPos.z << ")"
             << endl;*/

        //set the scale
        m_scaleMatrix = glm::scale(
                glm::mat4(1.0),
                m_scale);

        //assign value to transform based on rigid body's new world status
        //then update model with transform
        m_rigidBody->getMotionState()->getWorldTransform(transform);
        newTransform.getOpenGLMatrix(modelUpdate);
        model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
    }
}

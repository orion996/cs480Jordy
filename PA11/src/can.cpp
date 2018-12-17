#include "can.h"

Can::Can() : PhysicsObject()
{

}

Can::Can(string filename) : PhysicsObject(filename)
{

}

Can::Can(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

Can::Can(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh) : PhysicsObject(filename, scale, position, triMesh)
{

}

Can::~Can()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}


bool Can::Initialize()
{
  cout << "CHECK CAN INITIALIZE" << endl;

  //set transform
  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));

  //create the collider
  //m_collider = new btBvhTriangleMeshShape(m_colliderMesh, false);
    m_collider = new btCylinderShape(btVector3(
            m_scale.x * 2,
            m_scale.y * 2,
            m_scale.z * 2));

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

  m_rigidBody->setFriction(10000000.0);
  
  /*
    m_trigger = new TriggerObject(
      glm::vec3(1.0f, 1.0f, 1.0f) * m_scale,
      glm::vec3(m_position.x, m_position.y, m_position.z)                  
  );
  m_trigger->Initialize();*/

  //don't delete motion state
  //delete motionState;
  //motionState = NULL;
  
  model = m_translationMatrix;

  return true;
}

void Can::Update(unsigned int dt)
{
    btTransform transform, newTransform;
    btScalar modelUpdate[16];
    btVector3 origin = m_rigidBody->getWorldTransform().getOrigin();
    btMatrix3x3 basis = m_rigidBody->getWorldTransform().getBasis();

    
    m_position = glm::vec3(origin.x(), origin.y(), origin.z());
    
    //translate the collision box
    btVector3 newOrigin = btVector3(m_position.x, m_position.y, m_position.z);
    btQuaternion newRotation = btQuaternion::getIdentity();
    
    newTransform.setOrigin(newOrigin);
    newTransform.setBasis(basis);
    
    m_rigidBody->getMotionState()->setWorldTransform(newTransform);
    
    //translate the trigger
//     m_trigger->transformTrigger(newTransform);

    //set the scale
    m_scaleMatrix = glm::scale(
            glm::mat4(1.0),
            m_scale);

    //assign value to transform based on rigid body's new world status
    //then update model with transform
    m_rigidBody->getMotionState()->getWorldTransform(transform);
    //m_trigger->transformTrigger(transform);
    
    newTransform.getOpenGLMatrix(modelUpdate);
    model = glm::make_mat4(modelUpdate) * m_scaleMatrix;
}

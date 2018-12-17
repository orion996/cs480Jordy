#include "lane.h"

Lane::Lane() : PhysicsObject()
{

}

Lane::Lane(string filename) : PhysicsObject(filename)
{

}

Lane::Lane(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{

}

Lane::Lane(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh) : PhysicsObject(filename, scale, position, triMesh)
{

}

Lane::~Lane()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool Lane::Initialize(btTriangleMesh *triMesh)
{
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

    m_scaleMatrix = glm::scale(
      glm::mat4(1.0f),
      m_scale);
    
    m_collider = new btBvhTriangleMeshShape(triMesh, false);

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
    //m_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

    model = m_translationMatrix * m_scaleMatrix;

    return true;
}

void Lane::Update(unsigned int dt)
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
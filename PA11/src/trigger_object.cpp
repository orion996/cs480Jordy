#include "trigger_object.h"

TriggerObject::TriggerObject(glm::vec3 dimensions, glm::vec3 position)
{
  m_dimensions = dimensions;
  m_position = position;
  
  //create the collider
  m_collider = new btBoxShape(btVector3(
    m_dimensions.x,
    m_dimensions.y,
    m_dimensions.z));
}

TriggerObject::TriggerObject(glm::vec3 dimensions, glm::vec3 position, btCollisionShape* colShape)
{
  m_dimensions = dimensions;
  m_position = position;
  
  m_collider = colShape;
}

TriggerObject::~TriggerObject()
{
  delete m_collider;
  m_collider = NULL;
  delete m_ghostObject;
  m_ghostObject = NULL;
}

bool TriggerObject::Initialize()
{
  //set the transform
  btTransform transform(
    btQuaternion::getIdentity(),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));


  //create the collider object
  m_ghostObject = new btGhostObject();

  //set the collider
  m_ghostObject->setCollisionShape(m_collider);

  //disable contact reponse
  m_ghostObject->setCollisionFlags(
    m_ghostObject->getCollisionFlags() |
    btCollisionObject::CF_NO_CONTACT_RESPONSE);

  //apply the tranformation
  m_ghostObject->setWorldTransform(transform);

  return true;
}

void TriggerObject::Update(unsigned int dt)
{

}

void TriggerObject::transformTrigger(btTransform tf)
{
    m_ghostObject->setWorldTransform(tf);
}

glm::vec3 TriggerObject::GetPosition()
{
  return m_position;
}
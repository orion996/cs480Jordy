#include "physics_object.h"

PhysicsObject::PhysicsObject() : Object()
{

}

PhysicsObject::PhysicsObject(string filename) : Object(filename)
{

}

PhysicsObject::PhysicsObject(string filename, float scale, glm::vec3 position) : Object(filename, scale, position)
{

}

PhysicsObject::PhysicsObject(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh) : Object(filename, scale, position, triMesh)
{
  m_colliderMesh = triMesh;
}

PhysicsObject::~PhysicsObject()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

void PhysicsObject::Update(unsigned int dt)
{
  /*
  angleRotate += dt * (M_PI/5000) * m_rotateFactor;
  model = glm::rotate(glm::mat4(1.0), angleRotate, glm::vec3(0.0,1.0,0.0));
  
  model = glm::scale(
      model,
      glm::vec3(m_scaleVal, m_scaleVal, m_scaleVal)
    );
  */

  m_translationMatrix = glm::translate(
    glm::mat4(1.0f),
    m_position);

  m_rotationMatrix = glm::mat4(1.0f);

  m_scaleMatrix = glm::scale(
    glm::mat4(1.0),
    m_scale);

  model = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
}

/*
btCollisionShape* PhysicsObject::GetCollider()
{
  return m_collider;
}

btRigidBody* PhysicsObject::GetRigidBody()
{
  return m_rigidBody;
}
*/
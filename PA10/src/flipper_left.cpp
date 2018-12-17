#include "flipper_left.h"

FlipperLeft::FlipperLeft() : PhysicsObject()
{
  m_flipping = false;
  m_resetting = false;

  m_initialAngle = -2.355f; //-3pi/4
  m_thresholdAngle = -0.785f; //-pi/4
  m_currentAngle = m_initialAngle;

  m_flipAngleStep = 0.3f;
  m_resetAngleStep = -0.1f;
}

FlipperLeft::FlipperLeft(string filename) : PhysicsObject(filename)
{
  m_flipping = false;
  m_resetting = false;

  m_initialAngle = -2.355f;
  m_thresholdAngle = -1.047197551;
  m_currentAngle = m_initialAngle;

  m_flipAngleStep = 0.012f;
  m_resetAngleStep = -0.004f;
}

FlipperLeft::FlipperLeft(string filename, float scale, glm::vec3 position) : PhysicsObject(filename, scale, position)
{
  m_flipping = false;
  m_resetting = false;

  m_initialAngle = -2.355f;
  m_thresholdAngle = -1.047197551;
  m_currentAngle = m_initialAngle;

  m_flipAngleStep = 0.012f;
  m_resetAngleStep = -0.004f;
}

FlipperLeft::FlipperLeft(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh) : PhysicsObject(filename, scale, position, triMesh)
{
  m_flipping = false;
  m_resetting = false;

  m_initialAngle = -2.355f;
  m_thresholdAngle = -1.047197551;
  m_currentAngle = m_initialAngle;

  m_flipAngleStep = 0.012f;
  m_resetAngleStep = -0.004f;
}

FlipperLeft::~FlipperLeft()
{
  delete m_renderData;
  m_children.clear();
  delete m_collider;
  m_collider = NULL;
  delete m_rigidBody;
  m_rigidBody = NULL;
}

bool FlipperLeft::Initialize(btTriangleMesh *triMesh)
{
  cout << "CHECK FLIPPER INITIALIZE" << endl;

  float pi3Over2 = -3.14;

  //left flipper is opposite angle and steps
  /*
  if (m_left)
  {
    m_initialAngle *= -1;
    m_thresholdAngle *= -1;
    m_currentAngle = m_initialAngle;
    m_flipAngleStep *= -1;
    m_resetAngleStep *= -1;
    pi3Over2 *= -1;
  }
  */

  /*
  m_initialAngle *= -1;
  m_thresholdAngle *= -1;
  m_currentAngle = m_initialAngle;
  m_flipAngleStep *= -1;
  m_resetAngleStep *= -1;
  pi3Over2 *= -1;
  */

  //set transform
  btTransform transform(
    btQuaternion(m_initialAngle,0,0),
    btVector3(
      m_position.x,
      m_position.y,
      m_position.z));
  btScalar m[16];

  //rotate 90 degrees
  /*
  m_rotationMatrix = glm::rotate(
    glm::mat4(1.0f),
    (float) M_PI/2,
    glm::vec3(0.0f, 1.0f, 0.0f));
  */
  //rotate 0 degreess
  m_rotationMatrix = glm::rotate(
    glm::mat4(1.0f),
    (float) 0.0f,
    glm::vec3(0.0f, 1.0f, 0.0f));

  //m_scale.x *= -1;
  //m_scale.z *= -1;

  //set the scale
  m_scaleMatrix = glm::scale(
    glm::mat4(1.0),
    m_scale);

  //create the collider
  /*
  m_collider = new btBoxShape(btVector3(
    (m_scale.x) * 0.25,
    (m_scale.y) * 0.25,
    (m_scale.z) * 1));
  */
  m_collider = new btBvhTriangleMeshShape(triMesh, false);

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
  m_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);

  //get this origin
  btVector3 origin = m_rigidBody->getWorldTransform().getOrigin();

  //set pivot position
  float x_offset = sin(pi3Over2 + m_initialAngle) * (m_scale.x / 4);
  float z_offset = cos(pi3Over2 + m_initialAngle) * (m_scale.z / 4);
  m_pivotPosition = glm::vec3(
    origin.x() + x_offset,
    origin.y(),
    origin.z() + z_offset);

  //set inital position to correct offset
  m_position = glm::vec3(
    origin.x(),
    origin.y(),
    origin.z());
  float distanceToPivot = glm::distance(m_position, m_pivotPosition);
  btTransform offsetTransform(
    btQuaternion(m_initialAngle,0,0),
    btVector3(
      m_position.x + distanceToPivot * sin(m_currentAngle),
      m_position.y,
      m_position.z + distanceToPivot * cos(m_currentAngle)));
  m_rigidBody->getMotionState()->setWorldTransform(offsetTransform);
  
  //apply all transformations
  offsetTransform.getOpenGLMatrix(m);
  model = glm::make_mat4(m) * m_scaleMatrix;

  cout << "initial origin: "
       << "("
       << m_rigidBody->getWorldTransform().getOrigin().x() << ", "
       << m_rigidBody->getWorldTransform().getOrigin().y() << ", "
       << m_rigidBody->getWorldTransform().getOrigin().z() << ")"
       << endl;

  cout << "pivot origin: "
       << "("
       << m_pivotPosition.x << ", "
       << m_pivotPosition.y << ", "
       << m_pivotPosition.z << ")"
       << endl;

  cout << "FINISHED FLIPPER INITIALIZE" << endl;

  return true;
}

void FlipperLeft::Update(unsigned int dt)
{
  btTransform transform, newTransform;
  btVector3 origin;
  btMatrix3x3 basis;
  btScalar modelUpdate[16];
  float distanceToPivot;

  //get original origin and basis from transform
  origin = m_rigidBody->getWorldTransform().getOrigin();
  basis = m_rigidBody->getWorldTransform().getBasis();

  //set position to origin
  m_position = glm::vec3(
    origin.x(),
    origin.y(),
    origin.z());
  //cout << distanceToPivot << endl;

  //get the distance from origin to pivot
  distanceToPivot = glm::distance(m_position, m_pivotPosition);

  /*rotate on object pivot by correct step size*/

  if (m_flipping)
  {
    //check if above threshold
    if (abs(m_currentAngle) <= abs(m_thresholdAngle))
    {
      m_currentAngle = m_thresholdAngle;
      m_flipping = false;
      m_resetting = true;
    }
    //if not above threshold, set to next flip step
    else
    {

      m_currentAngle += m_flipAngleStep * dt;

      basis.setRotation(btQuaternion(
      m_currentAngle,
      0,
      0));

      newTransform.setOrigin(btVector3(
        m_pivotPosition.x + distanceToPivot * sin(m_currentAngle),
        m_pivotPosition.y,
        m_pivotPosition.z + distanceToPivot * cos(m_currentAngle)));
      newTransform.setBasis(basis);
      m_rigidBody->getMotionState()->setWorldTransform(newTransform);
    }
  }
  else if (m_resetting)
  {
    //check if below initial (resting point)
    if (abs(m_currentAngle) >= abs(m_initialAngle))
    {
      m_currentAngle = m_initialAngle;
      m_resetting = false;
    }
    //if not below resting point, set to next flip step
    else
    {

      m_currentAngle += m_resetAngleStep * dt;

      basis.setRotation(btQuaternion(
      m_currentAngle,
      0,
      0));

      newTransform.setOrigin(btVector3(
        m_pivotPosition.x + distanceToPivot * sin(m_currentAngle),
        m_pivotPosition.y,
        m_pivotPosition.z + distanceToPivot * cos(m_currentAngle)));
      newTransform.setBasis(basis);
      m_rigidBody->getMotionState()->setWorldTransform(newTransform);
    }
  }
  else
  {
    //default do nothing
  }

//   cout << "initial origin: "
//        << "("
//        << m_rigidBody->getWorldTransform().getOrigin().x() << ", "
//        << m_rigidBody->getWorldTransform().getOrigin().y() << ", "
//        << m_rigidBody->getWorldTransform().getOrigin().z() << ")"
//        << endl;

  //get the new transform of the rigid body
  m_rigidBody->getMotionState()->getWorldTransform(transform);
  
  //apply all transformations
  transform.getOpenGLMatrix(modelUpdate);
  model = glm::make_mat4(modelUpdate) * m_rotationMatrix * m_scaleMatrix;
}

void FlipperLeft::Flip()
{
  /*
  float x = 0.0f;
  float y = -5.0f;
  float z = 0.0f;
  
  //m_rigidBody->applyCentralImpulse(btVector3(.0, 0.0, 6.0));

  m_rigidBody->applyTorqueImpulse(btVector3(x,y,z));
  //m_rigidBody->getWorldTransform()*btVector3(x,y,z);
  //m_rigidBody->applyTorqueImpulse(btVector3(x,y,z));
  */
  m_flipping = true;
  m_resetting = false;
}

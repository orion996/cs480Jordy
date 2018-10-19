#include "camera.h"

Camera::Camera()
{
  m_position = glm::vec3(0.0, 0.0, -16.0);
  m_velocity = glm::vec3(0.0, 0.0, 0.0);
  m_focusPoint = glm::vec3(0.0, 0.0, 0.0);
  m_focusVector = m_position - m_focusPoint;

  m_moveSpeed = 2.0f;
  m_rotateSpeed = 5.0f;
  m_focusRadius = 1000.0;
  m_height = 0;
  m_maxHeight = 100.0f;
  m_pitch = 0.0f;
  m_yaw = 0.0f;

  m_mode = MODE_FOCUS;

  m_focusChanged = true;
}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt( m_position,                 //Eye Position
                      m_focusPoint,               //Focus point
                      glm::vec3(0.0, 1.0, 0.0));  //Positive Y is up

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 100000.0f); //Distance to the far plane, 
  return true;
}

void Camera::Update(unsigned int dt)
{
  //cout << m_mode << endl;

  //cout << m_moveSpeed << endl;
  //cout << m_defaultFocusRadius << endl;

  if (m_mode == MODE_FOCUS)
  {

    //float translateMultiplier = 50000;
    //float radius = glm::distance(m_position, m_focusPoint);
    //float xzRadius = glm::distance(glm::vec2(m_position.x, m_position.z),
    //                              glm::vec2(m_focusPoint.x, m_focusPoint.z));

    //cout << radius << endl;

    if (m_focusChanged)
    {
      m_focusRadius = m_defaultFocusRadius;
      m_height = m_defaultHeight;
      m_focusChanged = false;
    }

    if (m_velocity.y < 0)
    {
      //moving down
      if (m_height > m_maxHeight * -1)
      {
        m_height += m_velocity.y;
      }
    }
    else if (m_velocity.y > 0)
    {
      //moving up
      if (m_height < m_maxHeight)
      {
        m_height += m_velocity.y;
      }
    }

    if (m_velocity.z < 0)
    {
      m_focusRadius -= m_velocity.z;
    }
    else if (m_velocity.z > 0)
    {
      //only move if far enough away
      if (m_focusRadius > m_minFocusRadius)
      {
        m_focusRadius -= m_velocity.z;
      }
    }

    m_position = m_focusPoint;
    m_position.y += m_height;
    m_position.z -= m_focusRadius;

    /*
    if (m_velocity.x < 0)
    {
      //moving left
      m_moveAngleHrzt -= dt * (M_PI/translateMultiplier) / m_moveSpeed;
      m_position.x = xzRadius * sin(m_moveAngleHrzt) + m_focusPoint.x;
      m_position.z = xzRadius * cos(m_moveAngleHrzt) + m_focusPoint.z;
      //cout << m_moveAngleHrzt << endl;
    }
    else if (m_velocity.x > 0)
    {
      //moving right
      m_moveAngleHrzt += dt * (M_PI/translateMultiplier) / m_moveSpeed;
      m_position.x = xzRadius * sin(m_moveAngleHrzt) + m_focusPoint.x;
      m_position.z = xzRadius * cos(m_moveAngleHrzt) + m_focusPoint.z;
      //cout << m_moveAngleHrzt << endl;
    }
    */
    
  }
  else if (m_mode == MODE_FREE)
  {
    glm::vec3 localForward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 localUp = glm::vec3(0.0f, 1.0f, 0.0f);

    localForward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    localForward.y = sin(glm::radians(m_pitch));
    localForward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    localForward = glm::normalize(localForward);

    if (m_velocity.z > 0)
    {
      //move forward
      m_position += m_moveSpeed * localForward;
    }
    else if (m_velocity.z < 0)
    {
      //move back
      m_position -= m_moveSpeed * localForward;
    }

    if (m_velocity.x > 0)
    {
      //move right
      m_position += glm::normalize(glm::cross(localForward, localUp)) * m_moveSpeed;
    }
    else if (m_velocity.x < 0)
    {
      //move left
      m_position -= glm::normalize(glm::cross(localForward, localUp)) * m_moveSpeed;
    }

    m_focusPoint = m_position + localForward;


  }
  else if (m_mode == MODE_OVERVIEW)
  {

    if (m_focusChanged)
    {
      m_focusRadius = m_defaultFocusRadius;
      m_focusChanged = false;
    }

    m_focusPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    
    if (m_velocity.z < 0)
    {
      m_focusRadius -= m_velocity.z;
    }
    else if (m_velocity.z > 0)
    {
      //only move if far enough away
      if (m_focusRadius > m_minFocusRadius)
      {
        m_focusRadius -= m_velocity.z;
      }
    }

    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_position.y += m_focusRadius;
    m_position.z = 1.0f;
    
  }

  //cout << "(X: " << m_position.x << ", Y:" << m_position.y << ", Z: " << m_position.z << ")" << endl;
  
  view = glm::lookAt( m_position,                 //Eye Position
                      m_focusPoint,               //Focus point
                      glm::vec3(0.0, 1.0, 0.0));  //Positive Y is up
  
}

glm::mat4 Camera::CalculateFreeView(glm::vec3 eye, float pitch, float yaw)
{
  float pitchCos = cos(pitch);
  float pitchSin = sin(pitch);
  float yawCos = cos(yaw);
  float yawSin = sin(yaw);

  float viewMatrixData[16];

  viewMatrixData[0];

  glm::vec3 xAxis = glm::vec3(yawCos, 0, yawSin * -1);
  glm::vec3 yAxis = glm::vec3(yawSin * pitchSin, pitchCos, yawCos * pitchSin);
  glm::vec3 zAxis = glm::vec3(yawSin * pitchCos, pitchSin * -1, pitchCos * yawCos);

  glm::vec4 x = glm::vec4(xAxis.x, yAxis.x, zAxis.x, 0);
  glm::vec4 y = glm::vec4(xAxis.y, yAxis.y, zAxis.y, 0);
  glm::vec4 z = glm::vec4(xAxis.z, yAxis.z, zAxis.z, 0);
  glm::vec4 w = glm::vec4(glm::dot(xAxis, eye) * -1, glm::dot(yAxis, eye) * -1, glm::dot(zAxis, eye) * -1, 1);

  glm::mat4 freeView(x,y,z,w);

}

void Camera::HandleKeyboardInput(string input, bool isPressed)
{
  char input_key;

  if (input == "up")
  {
    if (m_mode == MODE_FREE)
    {
      if (isPressed)
      {
        //increase pitch
        m_pitch += m_rotateSpeed;

        if (m_pitch > 89.0f)
        {
          m_pitch = 89.0f;
        }
      }
    }
    else
    {
      if (isPressed)
      {
        SetVelocityY(1);
      }
      else
      {
        SetVelocityY(0);
      }
    }

    return;
  }
  else if (input == "down")
  {
    if (m_mode == MODE_FREE)
    {
      if (isPressed)
      {
        //decrease pitch
        m_pitch -= m_rotateSpeed;

        if (m_pitch < -89.0f)
        {
          m_pitch = -89.0f;
        }
      }
    }
    else
    {
      if (isPressed)
      {
        SetVelocityY(-1);
      }
      else
      {
        SetVelocityY(0);
      }
    }

    return;
  }
  else if (input == "left")
  {
    if (m_mode == MODE_FREE)
    {
      if (isPressed)
      {
        //decrease yaw
        m_yaw -= m_rotateSpeed;
      }
    }

    return;
  }
  else if (input == "right")
  {
    if (m_mode == MODE_FREE)
    {
      if (isPressed)
      {
        //increase yaw
        m_yaw += m_rotateSpeed;
      }
    }

    return;
  }

  input_key = input[0];

  switch(input_key)
  {
    case 'a':
      if (isPressed)
      {
        SetVelocityX(-1);
      }
      else
      {
        SetVelocityX(0);
      }
      break;
    case 'd':
      if (isPressed)
      {
        SetVelocityX(1);
      }
      else
      {
        SetVelocityX(0);
      }
      break;
    case 'w':
      if (isPressed)
      {
        SetVelocityZ(1);
      }
      else
      {
        SetVelocityZ(0);
      }
      break;
    case 's':
      if (isPressed)
      {
        SetVelocityZ(-1);
      }
      else
      {
        SetVelocityZ(0);
      }
      break;
    default:
      break;
  }
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}

glm::vec3 Camera::GetPosition()
{
  return m_position;
}

glm::vec3 Camera::GetVelocity()
{
  return m_velocity;
}

float Camera::GetMoveSpeed()
{
  return m_moveSpeed;
}

unsigned int Camera::GetMode()
{
  return m_mode;
}

float Camera::GetPositionX()
{
  return m_position.x;
}

float Camera::GetPositionY()
{
  return m_position.y;
}

float Camera::GetPositionZ()
{
  return m_position.z;
}

float Camera::GetVelocityX()
{
  return m_velocity.x;
}

float Camera::GetVelocityY()
{
  return m_velocity.y;
}

float Camera::GetVelocityZ()
{
  return m_velocity.z;
}

void Camera::SetParent(glm::mat4 parent)
{
  m_parent = parent;
}

void Camera::SetPosition(glm::vec3 position)
{
  m_position = position;
}

void Camera::SetPosition(float x, float y, float z)
{
  m_position = glm::vec3(x, y, z);
}

void Camera::SetVelocity(glm::vec3 velocity)
{
  m_velocity = velocity;
}

void Camera::SetVelocity(float x, float y, float z)
{
  m_velocity = glm::vec3(x, y, z);
}

void Camera::SetFocusPoint(glm::vec3 focusPoint)
{
  m_focusPoint = focusPoint;
}

void Camera::SetMoveSpeed(float moveSpeed)
{
  m_moveSpeed = moveSpeed;
}

void Camera::SetFocusRadius(float focusRadius)
{
  m_focusRadius = focusRadius;
}

void Camera::SetDefaultFocusRadius(float defaultFocusRadius)
{
  m_defaultFocusRadius = defaultFocusRadius;
}

void Camera::SetMinFocusRadius(float minFocusRadius)
{
  m_minFocusRadius = minFocusRadius;
}

void Camera::SetDefaultHeight(float defaultHeight)
{
  m_defaultHeight = defaultHeight;
}

void Camera::SetMaxHeight(float maxHeight)
{
  m_maxHeight = maxHeight;
}

void Camera::SetMode(unsigned int mode)
{
  m_mode = mode;
}

void Camera::SetFocusChanged(bool focusChanged)
{
  m_focusChanged = focusChanged;
}

void Camera::SetPositionX(float x)
{
  m_position.x = x;
}

void Camera::SetPositionY(float y)
{
  m_position.y = y;
}

void Camera::SetPositionZ(float z)
{
  m_position.z = z;
}

void Camera::SetVelocityX(float x)
{
  m_velocity.x = x * m_moveSpeed;
}

void Camera::SetVelocityY(float y)
{
  m_velocity.y = y * m_moveSpeed;
}

void Camera::SetVelocityZ(float z)
{
  m_velocity.z = z * m_moveSpeed;
}

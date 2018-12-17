#include "camera.h"

Camera::Camera()
{
  m_initialPosition = glm::vec3(10.0, 50.0, -100.0);
  m_position = m_initialPosition;
  m_initialFocusPoint = glm::vec3(10.0, 0.0, 0.0);
  m_focusPoint = m_initialFocusPoint;

  m_moveDirection = glm::vec3(0.0, 0.0, 0.0);
  m_moveSpeed = 0.01f;
  m_rotateSpeed = 5.0f;
  m_pitch = 0.0f;
  m_yaw = 0.0f;

  m_mode = MODE_GAME;
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
                                 5000.0f); //Distance to the far plane, 
  return true;
}

void Camera::Update(unsigned int dt)
{
  if (m_mode == MODE_GAME)
  {
    if (m_moveDirection.x > 0)
    {
      m_position.x += m_moveSpeed * ((float) dt);
    }
    else if (m_moveDirection.x < 0)
    {
      m_position.x -= m_moveSpeed * ((float) dt);
    }

    if (m_moveDirection.y > 0)
    {
      m_position.y += m_moveSpeed * ((float) dt);
    }
    else if (m_moveDirection.y < 0)
    {
      m_position.y -= m_moveSpeed * ((float) dt);
    }

    if (m_moveDirection.z > 0)
    {
      m_position.z += m_moveSpeed * ((float) dt);
      //cout << "moving forward" << endl;
    }
    else if (m_moveDirection.z < 0)
    {
      m_position.z -= m_moveSpeed * ((float) dt);
    }
  }
  else if (m_mode == MODE_FREE)
  {
    glm::vec3 localForward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 localUp = glm::vec3(0.0f, 1.0f, 0.0f);

    localForward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    localForward.y = sin(glm::radians(m_pitch));
    localForward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    localForward = glm::normalize(localForward);

    if (m_moveDirection.z > 0)
    {
      //move forward
      m_position += m_moveSpeed * localForward * ((float) dt);
    }
    else if (m_moveDirection.z < 0)
    {
      //move back
      m_position -= m_moveSpeed * localForward * ((float) dt);
    }

    if (m_moveDirection.x > 0)
    {
      //move right
      m_position -= glm::normalize(glm::cross(localForward, localUp)) * m_moveSpeed * ((float) dt);
    }
    else if (m_moveDirection.x < 0)
    {
      //move left
      m_position += glm::normalize(glm::cross(localForward, localUp)) * m_moveSpeed * ((float) dt);
    }

    m_focusPoint = m_position + localForward;
  }

  view = glm::lookAt( m_position,
    m_focusPoint,
    glm::vec3(0.0, 1.0, 0.0)); 
}

void Camera::Reset()
{
  m_position = m_initialPosition;
  m_focusPoint = m_initialFocusPoint;
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
        SetMoveDirectionY(1);
      }
      else
      {
        SetMoveDirectionY(0);
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
        SetMoveDirectionY(-1);
      }
      else
      {
        SetMoveDirectionY(0);
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
        SetMoveDirectionX(1);
      }
      else
      {
        SetMoveDirectionX(0);
      }
      break;
    case 'd':
      if (isPressed)
      {
        SetMoveDirectionX(-1);
      }
      else
      {
        SetMoveDirectionX(0);
      }
      break;
    case 'w':
      if (isPressed)
      {
        SetMoveDirectionZ(1);
      }
      else
      {
        SetMoveDirectionZ(0);
      }
      break;
    case 's':
      if (isPressed)
      {
        SetMoveDirectionZ(-1);
      }
      else
      {
        SetMoveDirectionZ(0);
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

glm::vec3 Camera::GetFocusPoint()
{
  return m_focusPoint;
}

float Camera::GetMoveDirectionX()
{
  return m_moveDirection.x;
}

float Camera::GetMoveDirectionY()
{
  return m_moveDirection.y;
}

float Camera::GetMoveDirectionZ()
{
  return m_moveDirection.z;
}

unsigned int Camera::GetMode()
{
  return m_mode;
}

void Camera::SetPosition(glm::vec3 position)
{
  m_position = position;
}

void Camera::SetFocusPoint(glm::vec3 focusPoint)
{
  m_focusPoint = focusPoint;
}

void Camera::SetMoveDirectionX(float x)
{
  m_moveDirection.x = x;
}

void Camera::SetMoveDirectionY(float y)
{
  m_moveDirection.y = y;
}

void Camera::SetMoveDirectionZ(float z)
{
  m_moveDirection.z = z;
}

void Camera::SetMode(unsigned int mode)
{
  m_mode = mode;
}
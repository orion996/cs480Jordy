#include "moon.h"

Moon::Moon()
{
	m_orbitRadius = 5.0f;
	m_spinSpeed = 1;
	m_orbitSpeed = 1;
  m_spinAngle = 0.0f;
}

Moon::Moon(float orbitRadius)
{
	m_orbitRadius = orbitRadius;
	m_spinSpeed = 1;
	m_orbitSpeed = 1;
  m_spinAngle = 0.0f;
}

Moon::Moon(float spinSpeed, float orbitSpeed)
{
	m_orbitRadius = 5.0f;
	m_spinSpeed = spinSpeed;
	m_orbitSpeed = orbitSpeed;
  m_spinAngle = 0.0f;
}

Moon::Moon(float orbitRadius, float spinSpeed, float orbitSpeed)
{
	m_orbitRadius = orbitRadius;
	m_spinSpeed = spinSpeed;
	m_orbitSpeed = orbitSpeed;
  m_spinAngle = 0.0f;
}

Moon::Moon(float orbitRadius, float spinSpeed, float orbitSpeed, string name, float scaleV)
{
    m_renderData = new Model();

    if (!m_renderData->LoadObject(name))
    {
        delete m_renderData;
        exit(1);
    }
    
    angleTranslate = 0.0f;
    angleRotate = 0.0f;

    m_paused = 0; //not paused
    m_spinDirection = 0; //spinning counter-clockwise
    m_orbitDirection = 0; //orbiting counter-clockwise
    
    m_orbitRadius = orbitRadius;
    m_spinSpeed = spinSpeed;
    m_orbitSpeed = orbitSpeed;
    m_scaleVal = scaleV;
    m_spinAngle = 0.0f;
}

Moon::~Moon()
{
	
}

void Moon::Update(unsigned int dt)
{
  //cout << "CHECK MOON UPDATE" << endl;

  //float radius = 6.0f;
  float rotateMultiplier = 10000;
  float translateMultiplier = 50000;

  if (!m_paused)
  {
    //update spin direction
    if (m_spinDirection == 0)
    {
      rotateMultiplier *= 1;
    }
    else
    {
      rotateMultiplier *= -1;
    }

    //update orbit direction
    if (m_orbitDirection == 0)
    {
      translateMultiplier *= 1;
    }
    else
    {
      translateMultiplier *= -1;
    }

    angleRotate += dt * (M_PI/rotateMultiplier) * m_spinSpeed;
    angleTranslate += dt * (M_PI/translateMultiplier) * m_orbitSpeed;

    translation = glm::translate(
      m_parent->GetTranslation(), 
      glm::vec3(
        m_orbitRadius * sin(angleTranslate), 
        0.0f, 
        m_orbitRadius * cos(angleTranslate)
      )
    );

    rotation = glm::rotate(
      glm::mat4(1.0f),
      m_spinAngle,
      glm::vec3(0.0, 0.0, 1.0)
    );

    rotation *= glm::rotate(
      glm::mat4(1.0f),
      angleRotate,
      glm::vec3(0.0, 1.0, 0.0)
    );

    scale = glm::scale(
   	  glm::mat4(1.0f),
   	  glm::vec3(m_scaleVal, m_scaleVal, m_scaleVal)
   	);

    //model = glm::translate(*m_parent, glm::vec3(radius * sin(angleTranslate), 0.0f, radius * cos(angleTranslate)));
    //model *= glm::rotate(glm::mat4(1.0f), (angleRotate), glm::vec3(0.0, 1.0, 0.0));
    //model = glm::translate(glm::mat4(1.0f), glm::vec3(0.01f * dt, 0.0f, 0.0f));

    model = translation * rotation * scale;    
  }
}

/*
void Moon::UpdateUranRing(unsigned int dt)
{
  //cout << "CHECK MOON UPDATE" << endl;

  //float radius = 6.0f;
  float rotateMultiplier = 10000;
  float translateMultiplier = 50000;

  if (!m_paused)
  {
    //update spin direction
    if (m_spinDirection == 0)
    {
      rotateMultiplier *= 1;
    }
    else
    {
      rotateMultiplier *= -1;
    }

    //update orbit direction
    if (m_orbitDirection == 0)
    {
      translateMultiplier *= 1;
    }
    else
    {
      translateMultiplier *= -1;
    }

    angleRotate += dt * (M_PI/rotateMultiplier) * m_spinSpeed;
    angleTranslate += dt * (M_PI/translateMultiplier) * m_orbitSpeed;

    translation = glm::translate(
      m_parent->GetTranslation(), 
      glm::vec3(
        m_orbitRadius * sin(angleTranslate), 
        0.0f, 
        m_orbitRadius * cos(angleTranslate)
      )
    );

    rotation = glm::rotate(
      glm::mat4(1.0f),
      -90.0f,
      glm::vec3(0.0, 0.0, 1.0)
    );

    rotation *= glm::rotate(
      glm::mat4(1.0f),
      angleRotate,
      glm::vec3(0.0, 1.0, 0.0)
    );

    scale = glm::scale(
   	  glm::mat4(1.0f),
   	  glm::vec3(m_scaleVal, m_scaleVal, m_scaleVal)
   	);

    //model = glm::translate(*m_parent, glm::vec3(radius * sin(angleTranslate), 0.0f, radius * cos(angleTranslate)));
    //model *= glm::rotate(glm::mat4(1.0f), (angleRotate), glm::vec3(0.0, 1.0, 0.0));
    //model = glm::translate(glm::mat4(1.0f), glm::vec3(0.01f * dt, 0.0f, 0.0f));

    model = translation * rotation * scale;    
  }
}
*/

float Moon::GetOrbitRadius()
{
	return m_orbitRadius;
}

float Moon::GetSpinSpeed()
{
	return m_spinSpeed;
}

float Moon::GetOrbitSpeed()
{
	return m_orbitSpeed;
}

void Moon::SetOrbitRadius(float orbitRadius)
{
	m_orbitRadius = orbitRadius;
}

void Moon::SetSpinSpeed(float spinSpeed)
{
	m_spinSpeed = spinSpeed;
}

void Moon::SetOrbitSpeed(float orbitSpeed)
{
	m_orbitSpeed = orbitSpeed;
}

void Moon::SetSpinAngle(float spinAngle)
{
  m_spinAngle = spinAngle;
}
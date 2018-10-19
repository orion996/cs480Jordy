#include "planet.h"

Planet::Planet()
{
	m_orbitRadius = 5.0f;
	m_spinSpeed = 1;
	m_orbitSpeed = 1;
  m_spinAngle = 0.0f;
}

Planet::Planet(float orbitRadius)
{
  cout << "in planet constructor" << endl;

	m_orbitRadius = orbitRadius;
	m_spinSpeed = 1;
	m_orbitSpeed = 1;
  m_spinAngle = 0.0f;
}

Planet::Planet(float spinSpeed, float orbitSpeed)
{
	m_orbitRadius = 5.0f;
	m_spinSpeed = spinSpeed;
	m_orbitSpeed = orbitSpeed;
  m_spinAngle = 0.0f;
}

Planet::Planet(float orbitRadius, float spinSpeed, float orbitSpeed)
{
	m_orbitRadius = orbitRadius;
	m_spinSpeed = spinSpeed;
	m_orbitSpeed = orbitSpeed;
  m_spinAngle = 0.0f;
}

Planet::Planet(float orbitRadius, float spinSpeed, float orbitSpeed, string name, float scaleV)
{
    m_renderData = new Model();

    if (!m_renderData->LoadObject(name))
    {
        delete m_renderData;
        exit(1);
    }

    //uncomment below to print all vertices
    /*
    cout << "Vertices:" << endl;
    cout << "{" << endl;
    for (int i = 0; i < Vertices.size(); i++)
    {
      cout << "{{"
           << Vertices[i].vertex.x
           << ", "
           << Vertices[i].vertex.y
           << ", "
           << Vertices[i].vertex.z
           << "}{"
           << Vertices[i].color.x
           << ", "
           << Vertices[i].color.y
           << ", "
           << Vertices[i].color.z
           << "}}" << endl;
    }
    cout << "}" << endl;
    //*/

    //uncomment below to print all indices
    /*
    cout << "Indices:" << endl;
    cout << "{" << endl;
    for (int i = 0; i < Indices.size(); i++)
    {
      cout << Indices[i] << " ";
      if (((i + 1) % 3) == 0) cout << endl;
    }
    cout << "}" << endl;
    //*/
    
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

Planet::~Planet()
{
  delete m_renderData;
}

void Planet::Update(unsigned int dt)
{
  //cout << "CHECK PLANET UPDATE" << endl;

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
    position = glm::vec3(
        m_orbitRadius * sin(angleTranslate), 
        0.0f, 
        m_orbitRadius * cos(angleTranslate)
    );

    translation = glm::translate(
      glm::mat4(1.0), 
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
void Planet::UpdateUran(unsigned int dt)
{
  //cout << "CHECK PLANET UPDATE" << endl;

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
    position = glm::vec3(
        m_orbitRadius * sin(angleTranslate), 
        0.0f, 
        m_orbitRadius * cos(angleTranslate)
    );

    translation = glm::translate(
      glm::mat4(1.0), 
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

float Planet::GetOrbitRadius()
{
	return m_orbitRadius;
}

float Planet::GetSpinSpeed()
{
	return m_spinSpeed;
}

float Planet::GetOrbitSpeed()
{
	return m_orbitSpeed;
}

void Planet::SetOrbitRadius(float orbitRadius)
{
	m_orbitRadius = orbitRadius;
}

void Planet::SetSpinSpeed(float spinSpeed)
{
	m_spinSpeed = spinSpeed;
}

void Planet::SetOrbitSpeed(float orbitSpeed)
{
	m_orbitSpeed = orbitSpeed;
}

void Planet::SetSpinAngle(float spinAngle)
{
  m_spinAngle = spinAngle;
}
#include "object.h"
Object::Object()
{ 
  m_parent = NULL;

  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8        */

  m_renderData = new Model();

  m_renderData->LoadObject();

  angleTranslate = 0.0f;
  angleRotate = 0.0f;

  m_paused = 0; //not paused
  m_spinDirection = 0; //spinning counter-clockwise
  m_orbitDirection = 0; //orbiting counter-clockwise
  m_rotateFactor = 1;
}

Object::Object(string filename, float scaleV)
{
  m_renderData = new Model();

  if (!m_renderData->LoadObject(filename))
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
  m_scaleVal = scaleV;
  m_rotateFactor = 1;
}

Object::~Object()
{
  delete m_renderData;
  m_children.clear();
}

void Object::Update(unsigned int dt)
{

  angleRotate += dt * (M_PI/5000) * m_rotateFactor;
  model = glm::rotate(glm::mat4(1.0), angleRotate, glm::vec3(0.0,1.0,0.0));
  
 model = glm::scale(
   	  model,
   	  glm::vec3(m_scaleVal, m_scaleVal, m_scaleVal)
   	);

  
}

void Object::Render()
{
  //m_renderData->Render();

  //cout << "render function entry" << endl;

  vector<GLuint> VBs = m_renderData->get_VBs();
  vector<GLuint> IBs = m_renderData->get_IBs();
  vector<unsigned int> numIndices = m_renderData->get_numIndices();

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  for ( int i = 0; i<VBs.size();i++) 
  {

    glBindBuffer(GL_ARRAY_BUFFER, VBs[i]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBs[i]);
    m_renderData->BindTexture(i);

    glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);

  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

glm::mat4 Object::GetModel()
{
  return model;
}

glm::mat4 Object::GetTranslation()
{
  return translation;
}

glm::mat4 Object::GetRotation()
{
  return rotation;
}

glm::mat4 Object::GetScale()
{
  return scale;
}

glm::vec3 Object::GetPosition()
{
  return position;
}

bool Object::IsPaused()
{
  return m_paused;
}

unsigned int Object::GetSpinDirection()
{
  return m_spinDirection;
}

unsigned int Object::GetOrbitDirection()
{
  return m_orbitDirection;
}

float Object::GetScaleVal()
{
  return m_scaleVal;
}

float Object::GetRotateFactor()
{
  return m_rotateFactor;
}

void Object::SetParent(Object* parent)
{
  m_parent = parent;
}

void Object::AddChild(Object* child)
{
  m_children.push_back(child);
}

void Object::RemoveChild()
{
  if (!m_children.empty())
  {
    m_children.pop_back();
  }
}

void Object::SetPaused(bool paused)
{
  m_paused = paused;
}

void Object::SetSpinDirection(unsigned int spinDirection)
{
  m_spinDirection = spinDirection;
}

void Object::SetOrbitDirection(unsigned int orbitDirection)
{
  m_orbitDirection = orbitDirection;
}

void Object::SetRotateFactor(float rotateFactor)
{
  m_rotateFactor = rotateFactor;
}
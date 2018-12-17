#include "object.h"
Object::Object()
{ 
  m_parent = NULL;
  m_renderData = new Model();
  if (!m_renderData->LoadObject())
  {
    delete m_renderData;
    exit(1);
  }

  m_position = glm::vec3(0.0f, 0.0f, 0.0f);
  m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

  m_rotationMatrix = glm::mat4(1.0);
}

Object::Object(string filename)
{
  m_parent = NULL;
  m_renderData = new Model();
  if (!m_renderData->LoadObject(filename))
  {
    delete m_renderData;
    exit(1);
  }

  m_position = glm::vec3(0.0f, 0.0f, 0.0f);
  m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

  m_rotationMatrix = glm::mat4(1.0);
}

Object::Object(string filename, float scale, glm::vec3 position)
{
  cout << "CHECK OBJECT CONSTRUCTOR" << endl;

  m_parent = NULL;
  m_renderData = new Model();
  if (!m_renderData->LoadObject(filename))
  {
    delete m_renderData;
    exit(1);
  }

  m_position = position;
  m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  m_scale = glm::vec3(1.0f * scale, 1.0f * scale, 1.0f * scale);

  m_rotationMatrix = glm::mat4(1.0);

  cout << "CHECK FINISHED OBJECT CONSTRUCTOR" << endl;
}

Object::Object(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh)
{
  cout << "CHECK OBJECT CONSTRUCTOR" << endl;

  m_parent = NULL;
  m_renderData = new Model();
  if (!m_renderData->LoadObject(filename, triMesh, scale))
  {
    delete m_renderData;
    exit(1);
  }

  m_position = position;
  m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  m_scale = glm::vec3(1.0f * scale, 1.0f * scale, 1.0f * scale);

  m_rotationMatrix = glm::mat4(1.0);

  cout << "CHECK FINISHED OBJECT CONSTRUCTOR" << endl;
}

Object::~Object()
{
  delete m_renderData;
  m_children.clear();
}

void Object::Update(unsigned int dt)
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

void Object::Render()
{
  vector<GLuint> VBs = m_renderData->get_VBs();
  vector<GLuint> IBs = m_renderData->get_IBs();
  vector<unsigned int> numIndices = m_renderData->get_numIndices();

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  for ( int i = 0; i<VBs.size();i++) 
  {

    glBindBuffer(GL_ARRAY_BUFFER, VBs[i]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBs[i]);
    m_renderData->BindTexture(i);

    glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);

  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

glm::mat4 Object::GetModel()
{
  return model;
}

glm::mat4 Object::GetTranslation()
{
  return m_translationMatrix;
}

glm::mat4 Object::GetRotation()
{
  return m_rotationMatrix;
}

glm::mat4 Object::GetScale()
{
  return m_scaleMatrix;
}

glm::vec3 Object::GetPosition()
{
  return m_position;
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

void Object::SetRotation(float angle, glm::vec3 rotation)
{
  m_rotation = rotation;
  m_rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, rotation);
}
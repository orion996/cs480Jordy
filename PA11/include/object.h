#ifndef OBJECT_H
#define OBJECT_H
#include "model.h"
#include <vector>
#include <string>
#include <time.h>
#include <math.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "graphics_headers.h"
#include <btBulletDynamicsCommon.h>

using namespace std;

struct Material
{
  string name;
  glm::vec3 color;
};

class Object
{
  public:
    Object();
    Object(string filename);
    Object(string filename, float scale, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
    Object(string filename, float scale, glm::vec3 position, btTriangleMesh *triMesh);

    virtual ~Object();

    virtual void Update(unsigned int dt);
    void Render();

    glm::mat4 GetModel();
    glm::mat4 GetTranslation();
    glm::mat4 GetRotation();
    glm::mat4 GetScale();
    glm::vec3 GetPosition();

    void SetParent(Object* parent);
    void AddChild(Object* child);
    void RemoveChild();

    void SetRotation(float angle, glm::vec3 rotation);

  protected:
    Object* m_parent;
    vector<Object*> m_children;

    Model* m_renderData;

    glm::mat4 model;
    glm::mat4 m_translationMatrix;
    glm::mat4 m_rotationMatrix;
    glm::mat4 m_scaleMatrix;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

#endif /* OBJECT_H */

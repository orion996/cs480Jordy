#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include <string>

using namespace std;

class Object
{
  public:
    Object(string fileName);
    ~Object();
    void Update(unsigned int dt);
    void Render();
    void LoadOBJ(string fileName);

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float angle;
};

#endif /* OBJECT_H */

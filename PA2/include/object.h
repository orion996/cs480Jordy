#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, char cmd);
    void Render();

    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float rotAngle;
    float orbitAngle;

    bool oReversed = false;
    bool rReversed = false;
    bool isOrbiting = true;
    bool isRotating = true;
};

#endif /* OBJECT_H */

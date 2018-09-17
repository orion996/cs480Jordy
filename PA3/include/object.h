#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, char cmd, bool newIn);
    void UpdateMoon(unsigned int dt, char cmd, glm::mat4 Planet, bool newIn);
    void Render();

    glm::mat4 GetModel();
    glm::mat4 GetMoonModel();

    Object *moons;

  private:
    glm::mat4 model;
    glm::mat4 moonModel;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float rotAngle;
    float orbitAngle;

    float mRotAngle;
    float mOrbitAngle;

    bool oReversed = false;
    bool rReversed = false;
    bool isOrbiting = true;
    bool isRotating = true;
};

#endif /* OBJECT_H */

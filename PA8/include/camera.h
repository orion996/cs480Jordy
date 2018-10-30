#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"
#include "graphics_headers.h"

using namespace std;

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    void Update(unsigned int dt);

    glm::mat4 GetProjection();
    glm::mat4 GetView();

    glm::vec3 GetPosition();
    glm::vec3 GetFocusPoint();

    void SetPosition(glm::vec3 position);
    void SetFocusPoint(glm::vec3 focusPoint);
  
  private:
    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 m_position;
    glm::vec3 m_focusPoint;
};

#endif /* CAMERA_H */

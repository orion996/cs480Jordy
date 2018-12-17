#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"
#include "graphics_headers.h"

using namespace std;

enum CameraMode {
  MODE_GAME = 0,
  MODE_FREE
};

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    void Update(unsigned int dt);
    void Reset();

    void HandleKeyboardInput(string input, bool isPressed);

    glm::mat4 GetProjection();
    glm::mat4 GetView();

    glm::vec3 GetPosition();
    glm::vec3 GetFocusPoint();
    float GetMoveDirectionX();
    float GetMoveDirectionY();
    float GetMoveDirectionZ();
    unsigned int GetMode();

    void SetPosition(glm::vec3 position);
    void SetFocusPoint(glm::vec3 focusPoint);
    void SetMoveDirectionX(float x);
    void SetMoveDirectionY(float y);
    void SetMoveDirectionZ(float z);
    void SetMode(unsigned int mode);
  
  private:
    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 m_initialPosition;
    glm::vec3 m_position;
    glm::vec3 m_initialFocusPoint;
    glm::vec3 m_focusPoint;

    glm::vec3 m_moveDirection;
    float m_moveSpeed;
    float m_rotateSpeed;
    float m_pitch;
    float m_yaw;

    unsigned int m_mode;
};

#endif /* CAMERA_H */

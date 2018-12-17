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
    void Reset();

    void HandleKeyboardInput(string input, bool isPressed);
    void HandleMouseMotion(int x, int y);

    void SwitchMode();

    glm::mat4 GetProjection();
    glm::mat4 GetView();
    glm::mat4 GetModel();

    glm::vec3 GetPosition();
    glm::vec3 GetFocusPoint();
    float GetMoveDirectionX();
    float GetMoveDirectionY();
    float GetMoveDirectionZ();
    float GetPitch();
    float GetYaw();

    void SetPosition(glm::vec3 position);
    void SetFocusPoint(glm::vec3 focusPoint);
    void SetMoveDirectionX(float x);
    void SetMoveDirectionY(float y);
    void SetMoveDirectionZ(float z);
    void SetDevMode(bool devMode);
  
  private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

    glm::vec3 m_initialPosition;
    glm::vec3 m_position;
    glm::vec3 m_initialFocusPoint;
    glm::vec3 m_focusPoint;

    glm::vec3 m_moveDirection;
    float m_moveSpeed;
    float m_rotateSpeed;
    float m_pitch;
    float m_yaw;
    float m_horizontalSensitivity;
    float m_verticalSensitivity;

    bool m_devMode = false;
};

#endif /* CAMERA_H */

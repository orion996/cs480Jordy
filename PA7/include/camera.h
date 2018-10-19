#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"
#include "graphics_headers.h"

using namespace std;

enum CameraMode {
    MODE_FOCUS = 0,
    MODE_FREE,
    MODE_OVERVIEW
};

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    void Update(unsigned int dt);

    glm::mat4 CalculateFreeView (
        glm::vec3 eye,
        float pitch,
        float yaw );

    //handle keyboard input
    void HandleKeyboardInput(string input, bool isPressed);

    glm::mat4 GetProjection();
    glm::mat4 GetView();
    glm::vec3 GetPosition();
    glm::vec3 GetVelocity();
    float GetMoveSpeed();
    unsigned int GetMode();

    //get individual x,y,z values
    float GetPositionX();
    float GetPositionY();
    float GetPositionZ();
    float GetVelocityX();
    float GetVelocityY();
    float GetVelocityZ();

    void SetParent(glm::mat4 parent);

    void SetPosition(glm::vec3 position);
    void SetPosition(float x, float y, float z);
    void SetVelocity(glm::vec3 velocity);
    void SetVelocity(float x, float y, float z);
    void SetFocusPoint(glm::vec3 focusPoint);

    void SetMoveSpeed(float moveSpeed);
    void SetFocusRadius(float focusRadius);
    void SetDefaultFocusRadius(float defaultFocusRadius);
    void SetMinFocusRadius(float minFocusRadius);
    void SetDefaultHeight(float defaultHeight);
    void SetMaxHeight(float maxHeight);
    void SetMode(unsigned int mode);
    void SetFocusChanged(bool focusChanged);

    //set individual x,y,z values
    void SetPositionX(float x);
    void SetPositionY(float y);
    void SetPositionZ(float z);
    void SetVelocityX(float x);
    void SetVelocityY(float y);
    void SetVelocityZ(float z);
  
  private:
    glm::mat4 projection;
    glm::mat4 view;

    glm::mat4 m_parent;

    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_focusPoint;
    glm::vec3 m_focusVector;

    float m_moveSpeed;
    float m_rotateSpeed;
    float m_focusRadius;
    float m_defaultFocusRadius;
    float m_minFocusRadius;
    float m_height;
    float m_defaultHeight;
    float m_maxHeight;
    float m_pitch;
    float m_yaw;

    unsigned int m_mode;

    bool m_focusChanged;
};

#endif /* CAMERA_H */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "planet.h"
#include "moon.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    void HandleCameraInput(string input);

    bool IsPlanetPaused();
    unsigned int GetPlanetSpin();
    unsigned int GetPlanetOrbit();
    bool IsMoonPaused();
    unsigned int GetMoonSpin();
    unsigned int GetMoonOrbit();

    void SetPlanetPaused(bool paused);
    void SetPlanetSpin(unsigned int spin);
    void SetPlanetOrbit(unsigned int orbit);
    void SetMoonPaused(bool paused);
    void SetMoonSpin(unsigned int spin);
    void SetMoonOrbit(unsigned int orbit);

    void SetCameraVelocity(glm::vec3 velocity);
    void SetCameraVelocity(float x, float y, float z);
    void SetCameraVelocity(char axis, float value);
    void SwitchCameraMode(void);
    void SetObjectFilename(string objectFilename);
    void ChangeFocusedObject(void);
    
    void CreatePlanets(string configFile);
    void UpdatePlanets(unsigned int dt);
    void RenderPlanets();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    //Object *m_object;
    Planet *m_planet[9];
    Moon *m_moon[100];
    Object *m_Sun;
    Moon *m_SatRing;
    
    int m_focusedObject;
    
    int moonIndex;

    string m_objectFilename;
};

#endif /* GRAPHICS_H */

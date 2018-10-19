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

    void HandleCameraInput(string input, bool isPressed);

    void SimulationSpeedUp();
    void SimulationSpeedDown();

    bool IsPlanetPaused();
    unsigned int GetPlanetSpin();
    unsigned int GetPlanetOrbit();
    bool IsMoonPaused();
    unsigned int GetMoonSpin();
    unsigned int GetMoonOrbit();

    unsigned int GetCameraMode();
    int GetFocusedObject();
    int GetSimulationSpeed();

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
    Planet *m_planet[9];
    Camera *m_camera;
  private:
    std::string ErrorString(GLenum error);


    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    //Object *m_object;
    Object *m_Sun;
    Object *m_Star;

    Moon *m_moon[500];
    Moon *m_SatRing;
    Moon *m_JupRing;
    Moon *m_UranRing;
    Moon *m_NepRing;
    //Planet *m_focusedObject;
    int m_focusedObject;

    int m_simulationSpeed;
    float m_simulationSpeedFactor;
    float m_cameraSpeed;
    float m_cameraSpeedFactor;
    float m_cameraDistanceOffset;
    float m_cameraDistanceFactor;
    float m_minCameraDistanceOffset;
    float m_minCameraDistanceFactor;
    float m_cameraHeightFactor;
    
    int moonIndex;

    string m_objectFilename;
};

#endif /* GRAPHICS_H */

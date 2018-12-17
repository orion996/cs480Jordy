#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "graphics_headers.h"
#include "world.h"
#include "camera.h"
#include "shader.h"
#include "light.h"

/*
struct Light
{
  glm::vec4 position;
  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;
  glm::vec3 direction;
  float angle;
  float shininess;
  float attenuation;
  bool directional;
};
*/

class Graphics
{
  public:
    Graphics();
    ~Graphics();

    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    void passLightToShader(int lightIndex, int shadowIndex);

    //void moveLight(char input);
    
    Shader *m_currentShader;
    Shader *m_vertexBasedShader;
    Shader *m_fragmentBasedShader;
    Shader *m_shadowDepthShader;

    World *m_world;
    Camera *m_camera;
    
    void shooooooooooot();

  private:
    std::string ErrorString(GLenum error);

    int m_windowWidth, m_windowHeight;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix; 

    vector<Light> m_lights;
    int m_numLights = 3;
    
    float* ambientMod;
    float* diffuseMod;
    float* specularMod;

    float ambientAdj = 0.5f;
    float diffuseAdj = 0.5f;
    float specularAdj = 0.5f;
};

#endif /* GRAPHICS_H */

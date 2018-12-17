#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "graphics_headers.h"
//#include "physics.h"
#include "world.h"
#include "camera.h"
#include "shader.h"
//#include "object.h"
//#include "board.h"

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
};

class Graphics
{
  public:
    Graphics();
    ~Graphics();

    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    void RenderBlank();

    void passLightToShader(int lightIndex);

    void AdjustSpecular(unsigned int object);

    void moveLight(char input);
    
    void changeShader();
    void ChangeLightIndex();
    void increaseBrightness();
    void decreaseBrightness();
    void increaseDiffuse();
    void decreaseDiffuse();
    void increaseSpecular(unsigned int object);
    void decreaseSpecular(unsigned int object);

    void increaseSpotLightRadius();
    void decreaseSpotLightRadius();

    int GetLightIndex();
    
    Shader *m_currentShader;
    Shader *m_vertexBasedShader;
    Shader *m_fragmentBasedShader;

    World *m_world;
    Camera *m_camera;

  private:
    std::string ErrorString(GLenum error);

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix; 

    vector<Light> m_lights;
    int m_numLights = 8;
    int m_currentLightIndex = 0;
    
    float* ambientMod;
    float* diffuseMod;

    float* boardSpecularMod;
    float* ballSpecularMod;
    float* flipperSpecularMod;
    float* cylinderSpecularMod;
    float* plungerSpecularMod;

    float ambientAdj = 0.5f;
    float diffuseAdj = 0.5f;
    float specularAdj = 0.5f;

    unsigned int m_currentShaderID;
};

#endif /* GRAPHICS_H */

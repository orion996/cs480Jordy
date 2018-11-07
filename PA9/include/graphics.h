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

    void moveFlipper(char input);
    void moveLight(char input);

    World *m_world;
    
    void changeShader();
    void increaseBrightness();
    void decreaseBrightness();

    void increaseCylSpecDiff();
    void decreaseCylSpecDiff();
    
    Shader *m_currentShader;
    Shader *m_vertexBasedShader;
    Shader *m_fragmentBasedShader;

  private:
    std::string ErrorString(GLenum error);

    //Physics *m_physics;
    
    Camera *m_camera;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix; 

    Light gLight;
    
    float ambientMod = 0;
 
    float cylSpecMod = 1;
    float cylDiffMod = .25;

    unsigned int m_currentShaderID;
};

#endif /* GRAPHICS_H */

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

class Graphics
{
  public:
    Graphics();
    ~Graphics();

    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();

    void moveFlipper(char input);

  private:
    std::string ErrorString(GLenum error);

    //Physics *m_physics;
    World *m_world;

    Camera *m_camera;

    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;    
};

#endif /* GRAPHICS_H */

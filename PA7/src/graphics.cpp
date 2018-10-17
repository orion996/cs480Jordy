#include "graphics.h"
#include <stdlib.h>

Graphics::Graphics()
{
  m_focusedObject = 0;
  moonIndex = 0;
}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
  //cout << "CHECK GRAPHICS INIT" << endl;

  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  CreatePlanets("planetData.txt");
  // Create the objects
//   m_object = new Object("..//assets//" + m_objectFilename);
//   m_planet[0] = new Planet(5.0, 5.0, 5.0);
//   m_moon = new Moon(30.0, 30.0);
// 
//   // Build the object hierarchy
//   m_planet->AddChild(m_moon);
//   m_moon->SetParent(m_planet);

  // Set up the shaders
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  //cout << "CHECK GRAPHICS UPDATE" << endl;

  // Update the objects

  /*m_object->Update(dt);
  m_planet->Update(dt);
  m_moon->Update(dt);*/
  UpdatePlanets(dt);

  if (m_focusedObject == 0)
  {
    m_camera->SetFocusPoint(m_Sun->GetPosition());
  }
  else
  {
    m_camera->SetFocusPoint(m_planet[m_focusedObject-1]->GetPosition());
  }
  
  m_camera->Update(dt);
}

void Graphics::Render()
{
  //cout << "CHECK GRAPHICS RENDER" << endl;

  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  // Render the objects
  RenderPlanets();

  //Object specified at command line
//   glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_object->GetModel()));
//   m_object->Render();

  //Planet
  //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_planet->GetModel()));
  //m_planet->Render();

  //Moon
  //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_moon->GetModel()));
  //m_moon->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::HandleCameraInput(string input)
{
  m_camera->HandleKeyboardInput(input);
}

// bool Graphics::IsPlanetPaused()
// {
//   return m_planet->IsPaused();
// }
// 
// unsigned int Graphics::GetPlanetSpin()
// {
//   return m_planet->GetSpinDirection();
// }
// 
// unsigned int Graphics::GetPlanetOrbit()
// {
//   return m_planet->GetOrbitDirection();
// }
// 
// void Graphics::SetPlanetPaused(bool paused)
// {
//   m_planet->SetPaused(paused);
// }
// 
// void Graphics::SetPlanetSpin(unsigned int spin)
// {
//   m_planet->SetSpinDirection(spin);
// }
// 
// void Graphics::SetPlanetOrbit(unsigned int orbit)
// {
//   m_planet->SetOrbitDirection(orbit);
// }

void Graphics::SetCameraVelocity(glm::vec3 velocity)
{
  m_camera->SetVelocity(velocity);
}

void Graphics::SetCameraVelocity(float x, float y, float z)
{
  m_camera->SetVelocity(x, y, z);
}

void Graphics::SetCameraVelocity(char axis, float value)
{
  switch (axis)
  {
    case 'x':
      m_camera->SetVelocityX(value);
      break;
    case 'y':
      m_camera->SetVelocityY(value);
      break;
    case 'z':
      m_camera->SetVelocityZ(value);
      break;
    case 'X':
      m_camera->SetVelocityX(value);
      break;
    case 'Y':
      m_camera->SetVelocityY(value);
      break;
    case 'Z':
      m_camera->SetVelocityZ(value);
      break;
    default:
      cout << "ERROR: Invalid camera velocity axis" << endl;
  }
}

void Graphics::SwitchCameraMode(void)
{
  if (m_camera->GetMode() == MODE_FOCUS)
  {
    m_camera->SetMode(MODE_FREE);
  }
  else if (m_camera->GetMode() == MODE_FREE)
  {
    m_camera->SetMode(MODE_OVERVIEW);
  }
  else if (m_camera->GetMode() == MODE_OVERVIEW)
  {
    m_camera->SetMode(MODE_FOCUS);
  }
}

void Graphics::SetObjectFilename(string objectFilename)
{
  m_objectFilename = objectFilename;
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

void Graphics::ChangeFocusedObject(void)
{
  if (m_focusedObject == 9)
  {
    m_focusedObject = 0;
  }
  else
  {
    m_focusedObject++;
  }
}

 void Graphics::CreatePlanets(string configFile)
 {
    //Source Code   
    /*// Create the objects
    m_object = new Object("..//assets//" + m_objectFilename);
    m_planet = new Planet(5.0, 5.0);
    m_moon = new Moon(30.0, 30.0);

    // Build the object hierarchy
    m_planet->AddChild(m_moon);
    m_moon->SetParent(m_planet);*/
    
    std::ifstream fin("..//assets//" + configFile);
    if(!fin.good())
        std::cerr << "ERROR OPENING CONFIG FILE" << std::endl;
    
    string name;
    float rotSpd, orbSpd, orbDist, moonRot, moonOrb, moonDist, planetScale, sunScale;
    int numMoons, moonMod;
    
    float speedMod = 5;
    float scaleMod = .05;
    
    //create sun
    fin >> name >> sunScale;
    m_Sun = new Object("..//assets//" + name + ".obj", sunScale * scaleMod);
    std::cout << std::endl;
    
    for(int i=0 ; i<9 ; i++)
    {
        fin >> name >> numMoons >> orbDist >> rotSpd >> orbSpd >> planetScale;
        m_planet[i] = new Planet((orbDist * sunScale * 25) * scaleMod , rotSpd * speedMod, orbSpd * speedMod, "..//assets//" + name + ".obj", planetScale * scaleMod);

        if(name == "Saturn")
        {
            m_SatRing = new Moon(0, .033 * speedMod, 0, "..//assets//SaturnRings.obj", planetScale * scaleMod * 2);
            m_planet[i]->AddChild(m_SatRing);
            m_SatRing->SetParent(m_planet[i]);
        }
        
        moonMod = 0;
    
        for(int j = moonIndex ; j < (moonIndex + numMoons) ; j++)
        {
            if(moonMod > 0)
                m_moon[j] = new Moon((planetScale * 60 * scaleMod) + (moonMod * 20 * scaleMod), .1 * speedMod + (rand() % 50), .1 * speedMod + (rand() % 50), "..//assets//Moon.obj", .27 * scaleMod * (rand() % 10) * .1);
            else
                m_moon[j] = new Moon((planetScale * 60 * scaleMod), .1 * speedMod, .1 * speedMod, "..//assets//Moon.obj", .27 * scaleMod);
            //std::cout << "Building Moon " << moonMod + 1 << " for " << name << " at index " << j << std::endl << std::endl; 
            
            m_planet[i]->AddChild(m_moon[j]);
            m_moon[j]->SetParent(m_planet[i]);
            
            moonMod++;
        }
        if(numMoons > 0)
            moonIndex += numMoons;
        
    }
    
    
    fin.close();
 }
 
 void Graphics::UpdatePlanets(unsigned int dt)
 {
     m_Sun->Update(dt);
     
     for(int i=0 ; i<9 ; i++)
        m_planet[i]->Update(dt);
     
     for(int i=0 ; i<moonIndex ; i++)
         m_moon[i]->Update(dt);
     
     m_SatRing -> Update(dt);
     
 }
 
 void Graphics::RenderPlanets()
 {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_Sun->GetModel()));
    m_Sun->Render();

    for(int i=0 ; i<9 ; i++)
    {
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_planet[i]->GetModel()));
        m_planet[i]->Render();
    }
    
     for(int i=0 ; i<moonIndex ; i++)
     {
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_moon[i]->GetModel()));
        m_moon[i]->Render();
     }
     
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_SatRing->GetModel()));
    m_SatRing->Render();

 }

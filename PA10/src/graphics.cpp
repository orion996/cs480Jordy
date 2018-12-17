#include "graphics.h"
#include <stdlib.h>

Graphics::Graphics()
{

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

  //Init Physics
  //m_physics = new Physics();

  //Init the world
  m_world = new World(glm::vec3(0.0f, -0.0005f, -0.00005f));
  if (!m_world->Initialize())
  {
    printf("World Failed to Initialize\n");
    return false;
  }

  cout << "CHECK GRAPHICS FINISHED PHYSICS AND WORLD ALLOC" << endl;

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  cout << "CHECK GRAPHICS FINISHED CAMERA ALLOC" << endl;

  // Init the objects
  //m_board = new Board("..//assets//Board.obj", 13.0f);

  //cout << "CHECK GRAPHICS FINISHED BOARD ALLOC" << endl;

  // Set up the shaders
  /*
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }
  */
  m_vertexBasedShader = new Shader();
  if (!m_vertexBasedShader->Initialize())
  {
    printf("Vertex based shader failed to initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_vertexBasedShader->AddShader(GL_VERTEX_SHADER, 0))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_vertexBasedShader->AddShader(GL_FRAGMENT_SHADER, 0))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_vertexBasedShader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Set up the shaders
  /*
  m_shader = new Shader();
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }
  */
  m_fragmentBasedShader = new Shader();
  if (!m_fragmentBasedShader->Initialize())
  {
    printf("Vertex based shader failed to initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_fragmentBasedShader->AddShader(GL_VERTEX_SHADER, 1))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_fragmentBasedShader->AddShader(GL_FRAGMENT_SHADER, 1))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_fragmentBasedShader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  //set which lighting type is currently being used (default is vertex-based)
  m_currentShader = m_vertexBasedShader;
  m_currentShaderID = 0;

  /* set the light data */

  /*
  gLight.position = glm::vec4(0.0f, 20.0f, 0.0f, 1.0f);
  gLight.ambient = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
  gLight.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  gLight.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  gLight.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  gLight.angle = 40.0f;
  gLight.shininess = 50;
  gLight.attenuation = 0.001f;
  */

  Light spotlight, pointLight1, pointLight2, pointLight3;
  Light cylSpotLight1, 
        cylSpotLight2,
        cylSpotLight3,
        cylSpotLight4,
        cylSpotLight5;

  spotlight.position = glm::vec4(0.0f, 20.0f, 0.0f, 1.0f);
  spotlight.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  spotlight.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  spotlight.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  spotlight.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  spotlight.angle = 40.0f;
  spotlight.shininess = 50;
  spotlight.attenuation = 0.001f;

  pointLight1.position = glm::vec4(-50.0f, 20.0f, 90.0f, 1.0f);
  pointLight1.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  pointLight1.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  pointLight1.specular = glm::vec4(3.0f, 3.0f, 3.0f, 3.0f);
  pointLight1.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  pointLight1.angle = 180.0f;
  pointLight1.shininess = 50;
  pointLight1.attenuation = 0.000001f;

  pointLight2.position = glm::vec4(50.0f, 20.0f, -50.0f, 1.0f);
  pointLight2.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  pointLight2.diffuse = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  pointLight2.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  pointLight2.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  pointLight2.angle = 180.0f;
  pointLight2.shininess = 50;
  pointLight2.attenuation = 0.000001f;

  pointLight3.position = glm::vec4(10.0f, 20.0f, 100.0f, 1.0f);
  pointLight3.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  pointLight3.diffuse = glm::vec4(4.0f, 4.0f, 4.0f, 1.0f);
  pointLight3.specular = glm::vec4(3.0f, 3.0f, 3.0f, 3.0f);
  pointLight3.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  pointLight3.angle = 180.0f;
  pointLight3.shininess = 50;
  pointLight3.attenuation = 0.001f;

  cylSpotLight1.position = glm::vec4(-7.0f, 20.0f, 50.0f, 1.0f);
  cylSpotLight1.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  cylSpotLight1.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  cylSpotLight1.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  cylSpotLight1.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  cylSpotLight1.angle = 40.0f;
  cylSpotLight1.shininess = 50;
  cylSpotLight1.attenuation = 0.001f;

  cylSpotLight2.position = glm::vec4(38.0f, 20.0f, 5.0f, 1.0f);
  cylSpotLight2.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  cylSpotLight2.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  cylSpotLight2.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  cylSpotLight2.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  cylSpotLight2.angle = 40.0f;
  cylSpotLight2.shininess = 50;
  cylSpotLight2.attenuation = 0.001f;

  cylSpotLight3.position = glm::vec4(23.0f, 20.0f, 50.0f, 1.0f);
  cylSpotLight3.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  cylSpotLight3.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  cylSpotLight3.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  cylSpotLight3.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  cylSpotLight3.angle = 40.0f;
  cylSpotLight3.shininess = 50;
  cylSpotLight3.attenuation = 0.001f;

  cylSpotLight4.position = glm::vec4(-22.0f, 20.0f, 5.0f, 1.0f);
  cylSpotLight4.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  cylSpotLight4.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  cylSpotLight4.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  cylSpotLight4.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  cylSpotLight4.angle = 40.0f;
  cylSpotLight4.shininess = 50;
  cylSpotLight4.attenuation = 0.001f;

  cylSpotLight5.position = glm::vec4(8.0f, 20.0f, 90.0f, 1.0f);
  cylSpotLight5.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  cylSpotLight5.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  cylSpotLight5.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  cylSpotLight5.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  cylSpotLight5.angle = 40.0f;
  cylSpotLight5.shininess = 50;
  cylSpotLight5.attenuation = 0.001f;

  m_lights.push_back(spotlight);
  m_lights.push_back(pointLight1);
  m_lights.push_back(pointLight2);
  //m_lights.push_back(pointLight3);
  m_lights.push_back(cylSpotLight1);
  m_lights.push_back(cylSpotLight2);
  m_lights.push_back(cylSpotLight3);
  m_lights.push_back(cylSpotLight4);
  m_lights.push_back(cylSpotLight5);

  ambientMod = new float[m_numLights];
  diffuseMod = new float[m_numLights];
  boardSpecularMod = new float[m_numLights];
  ballSpecularMod = new float[m_numLights];
  flipperSpecularMod = new float[m_numLights];
  cylinderSpecularMod = new float[m_numLights];
  plungerSpecularMod = new float[m_numLights];

  for (int i = 0; i < m_numLights; i++)
  {
    ambientMod[i] = 0;
    diffuseMod[i] = 0;
    boardSpecularMod[i] = 0;
    ballSpecularMod[i] = 0;
    flipperSpecularMod[i] = 0;
    cylinderSpecularMod[i] = 0;
    plungerSpecularMod[i] = 0;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_currentShader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_currentShader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_currentShader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  //glEnable(GL_LIGHTING);

  //enable transparency
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  cout << "CHECK GRAPHICS FINISHED INITIALIZE" << endl;

  return true;
}

void Graphics::Update(unsigned int dt)
{
  // Update the world
  m_world->Update(dt);

  // Update the spotlight
  glm::vec3 ballPos = m_world->GetBall().GetPosition();
  m_lights[0].position.x = ballPos.x;
  m_lights[0].position.z = ballPos.z;

  // Update the camera
  m_camera->Update(dt);
}

void Graphics::Render()
{

  // Clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_currentShader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  //Send in the number of lights
  glUniform1i(m_currentShader->GetUniformLocation("numLights"), m_numLights);

  /*
  //spotlight
  glUniform4f(m_currentShader->GetUniformLocation("lights[0].lightPosition"), 
    m_spotLight.position.x, m_spotLight.position.y, m_spotLight.position.z, 1.0);

  glUniform4f(m_currentShader->GetUniformLocation("lights[0].ambientProduct"),
    m_spotLight.ambient.x + ambientMod, m_spotLight.ambient.y + ambientMod, 
    m_spotLight.ambient.z + ambientMod, m_spotLight.ambient.w);
  glUniform4f(m_currentShader->GetUniformLocation("lights[0].diffuseProduct"),
    m_spotLight.diffuse.x + diffuseMod, m_spotLight.diffuse.y + diffuseMod, 
    m_spotLight.diffuse.z + diffuseMod, m_spotLight.diffuse.w);
  glUniform4f(m_currentShader->GetUniformLocation("lights[0].specularProduct"),
    m_spotLight.specular.x, m_spotLight.specular.y, 
    m_spotLight.specular.z, m_spotLight.specular.w);

  glUniform3f(m_currentShader->GetUniformLocation("lights[0].lightDirection"),
    m_spotLight.direction.x, m_spotLight.direction.y, m_spotLight.direction.z);
  glUniform1f(m_currentShader->GetUniformLocation("lights[0].lightAngle"),
    m_spotLight.angle);
  glUniform1f(m_currentShader->GetUniformLocation("lights[0].shininess"),
    m_spotLight.shininess);
  glUniform1f(m_currentShader->GetUniformLocation("lights[0].attenuationProduct"),
    m_spotLight.attenuation);

  //pointlight
  glUniform4f(m_currentShader->GetUniformLocation("lights[1].lightPosition"), 
    m_pointLight.position.x, m_pointLight.position.y, m_pointLight.position.z, 1.0);

  glUniform4f(m_currentShader->GetUniformLocation("lights[1].ambientProduct"),
    m_pointLight.ambient.x + ambientMod, m_pointLight.ambient.y + ambientMod, 
    m_pointLight.ambient.z + ambientMod, m_pointLight.ambient.w);
  glUniform4f(m_currentShader->GetUniformLocation("lights[1].diffuseProduct"),
    m_pointLight.diffuse.x + diffuseMod, m_pointLight.diffuse.y + diffuseMod, 
    m_pointLight.diffuse.z + diffuseMod, m_pointLight.diffuse.w);
  glUniform4f(m_currentShader->GetUniformLocation("lights[1].specularProduct"),
    m_pointLight.specular.x, m_pointLight.specular.y, 
    m_pointLight.specular.z, m_pointLight.specular.w);

  glUniform3f(m_currentShader->GetUniformLocation("lights[1].lightDirection"),
    m_pointLight.direction.x, m_pointLight.direction.y, m_pointLight.direction.z);
  glUniform1f(m_currentShader->GetUniformLocation("lights[1].lightAngle"),
    m_pointLight.angle);
  glUniform1f(m_currentShader->GetUniformLocation("lights[1].shininess"),
    m_pointLight.shininess);
  glUniform1f(m_currentShader->GetUniformLocation("lights[1].attenuationProduct"),
    m_pointLight.attenuation);
  */

  //Send the data for each light
  for (int i = 0; i < m_numLights; i++)
  {
    passLightToShader(i);
  }

  //Send in the texture sampler
  glUniform1i(m_currentShader->GetUniformLocation("gSampler"), 0);

  //render board
  /*
  glUniform4f(
    m_currentShader->GetUniformLocation("specularProduct"), 
    gLight.specular.x + boardSpecularMod, 
    gLight.specular.y + boardSpecularMod, 
    gLight.specular.z + boardSpecularMod, 
    gLight.specular.w);
  */
  
  AdjustSpecular(0);
  m_world->Render(m_modelMatrix, 'a');
  m_world->Render(m_modelMatrix, 't');

  //render ball
  /*
  glUniform4f(
    m_currentShader->GetUniformLocation("specularProduct"), 
    gLight.specular.x + ballSpecularMod, 
    gLight.specular.y + ballSpecularMod, 
    gLight.specular.z + ballSpecularMod, 
    gLight.specular.w);
  */

  AdjustSpecular(1);
  m_world->Render(m_modelMatrix, 'b');

  //render flippers
  /*
  glUniform4f(
    m_currentShader->GetUniformLocation("specularProduct"), 
    gLight.specular.x + flipperSpecularMod, 
    gLight.specular.y + flipperSpecularMod, 
    gLight.specular.z + flipperSpecularMod, 
    gLight.specular.w);
  */

  AdjustSpecular(2);
  m_world->Render(m_modelMatrix, 'f');

  //render plunger
  /*
  glUniform4f(
    m_currentShader->GetUniformLocation("specularProduct"),
    gLight.specular.x,
    gLight.specular.y,
    gLight.specular.z,
    gLight.specular.w);
  */

  AdjustSpecular(4);
  m_world->Render(m_modelMatrix, 'p');
  
  //render cylinders
  /*
  glUniform4f(
    m_currentShader->GetUniformLocation("specularProduct"), 
    gLight.specular.x + cylinderSpecularMod, 
    gLight.specular.y + cylinderSpecularMod, 
    gLight.specular.z + cylinderSpecularMod, 
    gLight.specular.w);
  */

  AdjustSpecular(3);
  m_world->Render(m_modelMatrix, 'c');

  //render launch barrier, lanes, and bumpers
  /*
  glUniform4f(
    m_currentShader->GetUniformLocation("specularProduct"),
    gLight.specular.x,
    gLight.specular.y,
    gLight.specular.z,
    gLight.specular.w);
  */

  AdjustSpecular(5);
  m_world->Render(m_modelMatrix, 'l');
  m_world->Render(m_modelMatrix, 'u');

  //cout << "finished rendering objects" << endl;

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::passLightToShader(int lightIndex)
{
  string lightArray = "lights[" + to_string(lightIndex) + "]";
  string variableName;

  //pass the light position
  variableName = lightArray + ".lightPosition";
  glUniform4f(m_currentShader->GetUniformLocation(variableName.c_str()), 
    m_lights[lightIndex].position.x, 
    m_lights[lightIndex].position.y, 
    m_lights[lightIndex].position.z, 
    1.0);

  //pass the lighting components
  variableName = lightArray + ".ambientProduct";
  glUniform4f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].ambient.x + ambientMod[lightIndex], 
    m_lights[lightIndex].ambient.y + ambientMod[lightIndex], 
    m_lights[lightIndex].ambient.z + ambientMod[lightIndex], 
    m_lights[lightIndex].ambient.w);
  variableName = lightArray + ".diffuseProduct";
  glUniform4f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].diffuse.x + diffuseMod[lightIndex], 
    m_lights[lightIndex].diffuse.y + diffuseMod[lightIndex], 
    m_lights[lightIndex].diffuse.z + diffuseMod[lightIndex], 
    m_lights[lightIndex].diffuse.w);
  variableName = lightArray + ".specularProduct";
  glUniform4f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].specular.x, 
    m_lights[lightIndex].specular.y, 
    m_lights[lightIndex].specular.z, 
    m_lights[lightIndex].specular.w);

  //pass additional lighting data
  variableName = lightArray + ".lightDirection";
  glUniform3f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].direction.x, 
    m_lights[lightIndex].direction.y, 
    m_lights[lightIndex].direction.z);
  variableName = lightArray + ".lightAngle";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].angle);
  variableName = lightArray + ".shininess";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].shininess);
  variableName = lightArray + ".attenuationProduct";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].attenuation);
}

void Graphics::AdjustSpecular(unsigned int object)
{
  

  switch (object)
  {
    case 0:
      for (int i = 0; i < m_numLights; i++)
      {
        string variableName = "lights[" + to_string(i) + "]";
        variableName += ".specularProduct";
        
        glUniform4f(
          m_currentShader->GetUniformLocation(variableName.c_str()), 
          m_lights[i].specular.x + boardSpecularMod[i], 
          m_lights[i].specular.y + boardSpecularMod[i], 
          m_lights[i].specular.z + boardSpecularMod[i], 
          m_lights[i].specular.w);
      }
    break;
    case 1:
      for (int i = 0; i < m_numLights; i++)
      {
        string variableName = "lights[" + to_string(i) + "]";
        variableName += ".specularProduct";
        
        glUniform4f(
          m_currentShader->GetUniformLocation(variableName.c_str()), 
          m_lights[i].specular.x + ballSpecularMod[i], 
          m_lights[i].specular.y + ballSpecularMod[i], 
          m_lights[i].specular.z + ballSpecularMod[i], 
          m_lights[i].specular.w);
      }
    break;
    case 2:
      for (int i = 0; i < m_numLights; i++)
      {
        string variableName = "lights[" + to_string(i) + "]";
        variableName += ".specularProduct";
        
        glUniform4f(
          m_currentShader->GetUniformLocation(variableName.c_str()), 
          m_lights[i].specular.x + flipperSpecularMod[i], 
          m_lights[i].specular.y + flipperSpecularMod[i], 
          m_lights[i].specular.z + flipperSpecularMod[i], 
          m_lights[i].specular.w);
      }
    break;
    case 3:
      for (int i = 0; i < m_numLights; i++)
      {
        string variableName = "lights[" + to_string(i) + "]";
        variableName += ".specularProduct";
        
        glUniform4f(
          m_currentShader->GetUniformLocation(variableName.c_str()), 
          m_lights[i].specular.x + cylinderSpecularMod[i], 
          m_lights[i].specular.y + cylinderSpecularMod[i], 
          m_lights[i].specular.z + cylinderSpecularMod[i], 
          m_lights[i].specular.w);
      }
    break;
    case 4:
      for (int i = 0; i < m_numLights; i++)
      {
        string variableName = "lights[" + to_string(i) + "]";
        variableName += ".specularProduct";
        
        glUniform4f(
          m_currentShader->GetUniformLocation(variableName.c_str()), 
          m_lights[i].specular.x + plungerSpecularMod[i], 
          m_lights[i].specular.y + plungerSpecularMod[i], 
          m_lights[i].specular.z + plungerSpecularMod[i], 
          m_lights[i].specular.w);
      }
    break;
    case 5:
      for (int i = 0; i < m_numLights; i++)
      {
        string variableName = "lights[" + to_string(i) + "]";
        variableName += ".specularProduct";
        
        glUniform4f(
          m_currentShader->GetUniformLocation(variableName.c_str()), 
          m_lights[i].specular.x, 
          m_lights[i].specular.y, 
          m_lights[i].specular.z, 
          m_lights[i].specular.w);
      }
    break;
    default:break;
  }

  
}

void Graphics::ChangeLightIndex()
{
  m_currentLightIndex++;
  if (m_currentLightIndex >= m_numLights)
  {
    m_currentLightIndex = 0;
  }
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

/*
void Graphics::moveLight(char input)
{
  switch (input)
  {
    case 'w':
      gLight.position.z += 1;
      break;
    case 'a':
      gLight.position.x += 1;
      break;
    case 's':
      gLight.position.z -= 1;
      break;
    case 'd':
      gLight.position.x -= 1;
      break;
    case '+':
      gLight.position.y += 1;
      break;
    case '-':
      gLight.position.y -= 1;
      break;
    case '^':
      gLight.direction.z += 0.1;
      break;
    case 'v':
      gLight.direction.z -= 0.1;
      break;
    case '<':
      gLight.direction.x += 0.1;
      break;
    case '>':
      gLight.direction.x -= 0.1;
      break;
    default: break;
  }
}
*/

void Graphics::changeShader()
{
  if (m_currentShaderID == 0)
  {
    cout << "Changing to fragment based lighting" << endl;
    m_currentShader = m_fragmentBasedShader;
    m_currentShaderID = 1;
  }
  else
  {
    cout << "Changing to vertex based lighting" << endl;
    m_currentShader = m_vertexBasedShader;
    m_currentShaderID = 0;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_currentShader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    //return;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_currentShader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    //return;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_currentShader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    //return;
  }
}

void Graphics::increaseBrightness()
{
    ambientMod[m_currentLightIndex] += .05;
    cout << "Object " << m_currentLightIndex << "'s scene brightness set to " << ambientMod[m_currentLightIndex] << endl;
}

void Graphics::decreaseBrightness()
{
    ambientMod[m_currentLightIndex] -= .05;
    cout << "Object " << m_currentLightIndex << "'s scene brightness set to " << ambientMod[m_currentLightIndex] << endl;
}

void Graphics::increaseDiffuse()
{
  diffuseMod[m_currentLightIndex] += diffuseAdj;
  cout << "Diffuse modifier set to " << diffuseMod[m_currentLightIndex] << endl;
  //cout << "Spot light brightness set to " << diffuseMod << endl;
}

void Graphics::decreaseDiffuse()
{
  diffuseMod[m_currentLightIndex] -= diffuseAdj;
  cout << "Diffuse modifier set to " << diffuseMod[m_currentLightIndex] << endl;
  //cout << "Spot light brightness set to " << diffuseMod << endl;
}

void Graphics::increaseSpecular(unsigned int object)
{
  switch (object)
  {
    case 0:
      boardSpecularMod[m_currentLightIndex] += specularAdj;
      cout << "Board specular set to " << boardSpecularMod[m_currentLightIndex] << endl;
      break;
    case 1:
      ballSpecularMod[m_currentLightIndex] += specularAdj;
      cout << "Ball specular set to " << ballSpecularMod[m_currentLightIndex] << endl;
      break;
    case 2:
      flipperSpecularMod[m_currentLightIndex] += specularAdj;
      cout << "Flipper specular set to " << flipperSpecularMod[m_currentLightIndex] << endl;
      break;
    case 3:
      cylinderSpecularMod[m_currentLightIndex] += specularAdj;
      cout << "Cylinder specular set to " << cylinderSpecularMod[m_currentLightIndex] << endl;
      break;
    case 4:
      plungerSpecularMod[m_currentLightIndex] += specularAdj;
      cout << "Plunger specular set to " << plungerSpecularMod[m_currentLightIndex] << endl;
      break;
    default: break;
  }
}

void Graphics::decreaseSpecular(unsigned int object)
{
  switch (object)
  {
    case 0:
      boardSpecularMod[m_currentLightIndex] -= specularAdj;
      cout << "Board specular set to " << boardSpecularMod[m_currentLightIndex] << endl;
      break;
    case 1:
      ballSpecularMod[m_currentLightIndex] -= specularAdj;
      cout << "Ball specular set to " << ballSpecularMod[m_currentLightIndex] << endl;
      break;
    case 2:
      flipperSpecularMod[m_currentLightIndex] -= specularAdj;
      cout << "Flipper specular set to " << flipperSpecularMod[m_currentLightIndex] << endl;
      break;
    case 3:
      cylinderSpecularMod[m_currentLightIndex] -= specularAdj;
      cout << "Cylinder specular set to " << cylinderSpecularMod[m_currentLightIndex] << endl;
      break;
    case 4:
      plungerSpecularMod[m_currentLightIndex] -= specularAdj;
      cout << "Plunger specular set to " << plungerSpecularMod[m_currentLightIndex] << endl;
      break;
    default: break;
  }
}

void Graphics::increaseSpotLightRadius()
{
  if (m_lights[0].angle < 180.0f)
  {
    m_lights[0].angle += 1.0f;
  }
  cout << "Spot light angle set to " << m_lights[0].angle << " degrees" << endl;
}

void Graphics::decreaseSpotLightRadius()
{
  if (m_lights[0].angle > 0.0f)
  {
    m_lights[0].angle -= 1.0f;
  }
  cout << "Spot light angle set to " << m_lights[0].angle << " degrees" << endl;
}

int Graphics::GetLightIndex()
{
  return m_currentLightIndex;
}
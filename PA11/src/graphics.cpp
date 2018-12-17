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

  m_windowWidth = width;
  m_windowHeight = height;

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Init Physics
  //m_physics = new Physics();

   // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  cout << "CHECK GRAPHICS FINISHED CAMERA ALLOC" << endl;

  //Init the world
  m_world = new World(glm::vec3(0.0f, -0.00005f, 0.0f));
  if (!m_world->Initialize())
  {
    printf("World Failed to Initialize\n");
    return false;
  }

  cout << "CHECK GRAPHICS FINISHED PHYSICS AND WORLD ALLOC" << endl;

  // Set up the shaders
  m_fragmentBasedShader = new Shader();
  if (!m_fragmentBasedShader->Initialize())
  {
    printf("Vertex based shader failed to initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_fragmentBasedShader->AddShader(GL_VERTEX_SHADER, "lighting.vert"))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_fragmentBasedShader->AddShader(GL_FRAGMENT_SHADER, "lighting.frag"))
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

  m_currentShader = m_fragmentBasedShader;

  // Set up the shadow depth shader
  m_shadowDepthShader = new Shader();
  if (!m_shadowDepthShader->Initialize())
  {
    printf("Shadow depth shader failed to initialize\n");
    return false;
  }

  // Add the vertex shader
  if (!m_shadowDepthShader->AddShader(GL_VERTEX_SHADER, "shadow_depth.vert"))
  {
    printf("Vertex Shader failed to initialize\n");
    return false;
  }

  // Add the fragment shader
  if (!m_shadowDepthShader->AddShader(GL_FRAGMENT_SHADER, "shadow_depth.frag"))
  {
    printf("Fragment Shader failed to initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shadowDepthShader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  /* set the light data */

  Light mainLight, outsideLight, spotLight;

  mainLight.position = glm::vec4(-50.0f, 25.0f, 65.0f, 1.0f);
  mainLight.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  mainLight.diffuse = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
  mainLight.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
  mainLight.focusPoint = glm::vec3(-20.0f, 6.0f, -50.0f);
  mainLight.angle = 50.0f;
  mainLight.shininess = 50;
  mainLight.attenuation = 0.000001f;
  mainLight.directional = false;
  mainLight.castsShadows = true;
  mainLight.x_ortho = 50;
  mainLight.y_ortho = 50;
  mainLight.near_plane = 5.0;
  mainLight.far_plane = 200;

  mainLight.Initialize();

  m_lights.push_back(mainLight);

  outsideLight.position = glm::vec4(60.0f, 80.0f, 120.0f, 1.0f);
  outsideLight.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  outsideLight.diffuse = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
  outsideLight.specular = glm::vec4(3.0f, 3.0f, 3.0f, 3.0f);
  outsideLight.focusPoint = glm::vec3(0.0f, 0.0f, 0.0f);
  outsideLight.angle = 10.0f;
  outsideLight.shininess = 50;
  outsideLight.attenuation = 0.000001f;
  outsideLight.directional = true;
  outsideLight.castsShadows = true;
  outsideLight.x_ortho = 100;
  outsideLight.y_ortho = 150;
  outsideLight.near_plane = 10;
  outsideLight.far_plane = 500;

  outsideLight.Initialize();

  m_lights.push_back(outsideLight);

  spotLight.position = glm::vec4(0, 30, 0, 1.0);
  spotLight.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
  spotLight.diffuse = glm::vec4(1.5f, 1.5f, 1.5f, 1.0f);
  spotLight.specular = glm::vec4(3.0f, 3.0f, 3.0f, 1.0f);
  spotLight.focusPoint = glm::vec3(50.0f, 12.0f, 0.0f);
  spotLight.angle = 25.0f;
  spotLight.shininess = 50;
  spotLight.attenuation = 0.000001f;
  spotLight.directional = false;
  spotLight.castsShadows = true;
  spotLight.near_plane = 1.0;
  spotLight.far_plane = 50;

  spotLight.Initialize();

  m_lights.push_back(spotLight);

  ambientMod = new float[m_numLights];
  diffuseMod = new float[m_numLights];
  specularMod = new float[m_numLights];

  for (int i = 0; i < m_numLights; i++)
  {
    ambientMod[i] = 0;
    diffuseMod[i] = 0;
    specularMod[i] = 0;
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
  // Update the camera
  m_camera->Update(dt);

  // Update the world
  m_world->m_cameraTransform = m_camera->GetModel();
  m_world->Update(dt);
}

void Graphics::Render()
{

  //cout << "CHECK GRAPHICS RENDER ENTRY" << endl;

  // Clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
  // Render scene from light's perspective
 // cout << "rendering from lights perspective" << endl; 
  m_shadowDepthShader->Enable();

  glCullFace(GL_FRONT);

  glUniform1i(m_currentShader->GetUniformLocation("depthMap"), 0);

  for (int i = 0; i < m_numLights; i++)
  {
    if (m_lights[i].castsShadows)
    {
      m_lights[i].Bind(*m_shadowDepthShader);

      /* render the objects */

      //render generic objects
      m_world->Render();

      //render specific objects
      for (int j = 0; j < m_world->GetObjectCount(); j++)
      {
        m_world->Render(*m_shadowDepthShader, m_lights, j);
      }

      m_lights[i].Reset();
    }
  }

  //cout << "finished rendering from lights perspective" << endl;

  glViewport(0, 0, m_windowWidth, m_windowHeight);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_currentShader->Enable();

  glCullFace(GL_BACK);

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  //glm::mat4 lightMatrix = m_lights[0].GetProjection() * m_lights[0].GetView();
  //GLint lightMatrixLocation = m_currentShader->GetUniformLocation("lightMatrix");
  //glUniformMatrix4fv(lightMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightMatrix)); 

  //Send in the number of lights
  glUniform1i(m_currentShader->GetUniformLocation("numLights"), m_numLights);

  //Send the data for each light
  int shadowIndex = 0;
  for (int i = 0; i < m_numLights; i++)
  {
    passLightToShader(i, shadowIndex);
    if (m_lights[i].castsShadows)
    {
      shadowIndex++;
    }
  }

  // Send in the camera position
  glm::vec3 cameraPosition = m_camera->GetPosition();
  glUniform3f(
    m_currentShader->GetUniformLocation("cameraPosition"),
    cameraPosition.x,
    cameraPosition.y,
    cameraPosition.z);

  //Send in the texture sampler
  glUniform1i(m_currentShader->GetUniformLocation("gSampler"), 0);
  //glUniform1i(m_currentShader->GetUniformLocation("shadowMap"), 1);

  //bind the depth maps
  GLenum shadowMapIndex = GL_TEXTURE1;
  for (int i = 0; i < m_numLights; i++)
  {
    if (m_lights[i].castsShadows)
    {
      glActiveTexture(shadowMapIndex);
      glBindTexture(GL_TEXTURE_2D, m_lights[i].GetShadow().GetDepthMap());
      shadowMapIndex++;
    }
  }

  /* render the objects */

  //render generic objects
  m_world->Render();

  //render specific objects
  for (int i = 0; i < m_world->GetObjectCount(); i++)
  {
    m_world->Render(*m_currentShader, m_lights, i);
  }

  //cout << "finished rendering objects" << endl;

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
  
}

void Graphics::passLightToShader(int lightIndex, int shadowIndex)
{
  string lightArray = "lights[" + to_string(lightIndex) + "]";
  string variableName;

  // pass the light matrix
  glm::mat4 lightMatrix = m_lights[lightIndex].GetProjection() 
    * m_lights[lightIndex].GetView();
  variableName = lightArray + ".lightMatrix";
  GLint lightMatrixLocation = m_currentShader->GetUniformLocation(variableName.c_str());
  glUniformMatrix4fv(
    lightMatrixLocation, 
    1, 
    GL_FALSE, 
    glm::value_ptr(lightMatrix)); 

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

  glm::vec3 lightDirection = m_lights[lightIndex].focusPoint - glm::vec3(
    m_lights[lightIndex].position.x,
    m_lights[lightIndex].position.y,
    m_lights[lightIndex].position.z);
//   cout << "light direction: "
//        << lightDirection.x << ", "
//        << lightDirection.y << ", "
//        << lightDirection.z << endl;
  variableName = lightArray + ".lightDirection";
  glUniform3f(m_currentShader->GetUniformLocation(variableName.c_str()),
    lightDirection.x, 
    lightDirection.y, 
    lightDirection.z);

  variableName = lightArray + ".lightAngle";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].angle);

  variableName = lightArray + ".shininess";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].shininess);

  variableName = lightArray + ".attenuationProduct";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].attenuation);

  variableName = lightArray + ".directional";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].directional);

  variableName = lightArray + ".shadowed";
  glUniform1f(m_currentShader->GetUniformLocation(variableName.c_str()),
    m_lights[lightIndex].castsShadows);

  // if the light casts shadows, send in the depth map sampler data
  if (m_lights[lightIndex].castsShadows)
  {
    variableName = "shadowMap[" + to_string(lightIndex) + "]";
    glUniform1i(m_currentShader->GetUniformLocation(variableName.c_str()), 
    shadowIndex + 1);
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

void Graphics::shooooooooooot()
{
    glm::vec3 pos = m_camera->GetPosition();
    
    //cout << "POSITION: " << pos.x << " " << pos.y << " "  << pos.z << endl;
    
    m_world->createBullet(pos.x, pos.y, pos.z, m_camera->GetPitch(), m_camera->GetYaw());
}


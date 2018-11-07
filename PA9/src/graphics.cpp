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
  m_world = new World(glm::vec3(0.0f, -0.005f, -0.0001f));
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

  //set light dataS
  gLight.position = glm::vec4(0.0f, 20.0f, 0.0f, 1.0f);
  gLight.ambient = glm::vec4(0.1, 0.1, 0.1, 1.0f);
  gLight.diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  gLight.specular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
  gLight.direction = glm::vec3(0.0f, -1.0f, 0.0f);
  gLight.angle = 20.0f;
  gLight.shininess = 50;
  gLight.attenuation = 0.00001f;

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
  //cout << "CHECK GRAPHICS UPDATE" << endl;

  // Update the physics world
  //m_physics->Update(dt);

  // Update the objects
  //m_board->Update(dt);

  // Update the world
  m_world->Update(dt);

  // Update the lights
  glm::vec3 ballPos = m_world->GetBall().GetPosition();
  gLight.position.x = ballPos.x;
  gLight.position.z = ballPos.z;

  // Update the camera
  m_camera->Update(dt);
}

void Graphics::Render()
{
  //cout << "CHECK GRAPHICS RENDER" << endl;
//   cout << "("
//        << gLight.position.x << ", "
//        << gLight.position.y << ", "
//        << gLight.position.z << ")"
//        << endl;

  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_currentShader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  glUniform4f(m_currentShader->GetUniformLocation("lightPosition"), gLight.position.x, gLight.position.y, gLight.position.z, 1.0);
  glUniform4f(m_currentShader->GetUniformLocation("ambientProduct"), gLight.ambient.x + ambientMod, gLight.ambient.y + ambientMod, gLight.ambient.z + ambientMod, gLight.ambient.w);
  glUniform4f(m_currentShader->GetUniformLocation("diffuseProduct"), gLight.diffuse.x, gLight.diffuse.y, gLight.diffuse.z, gLight.diffuse.w);
  glUniform4f(m_currentShader->GetUniformLocation("specularProduct"), gLight.specular.x, gLight.specular.y, gLight.specular.z, gLight.specular.w);
  glUniform3f(m_currentShader->GetUniformLocation("lightDirection"), gLight.direction.x, gLight.direction.y, gLight.direction.z);
  glUniform1f(m_currentShader->GetUniformLocation("lightAngle"), gLight.angle);
  glUniform1f(m_currentShader->GetUniformLocation("shininess"), gLight.shininess);
  glUniform1f(m_currentShader->GetUniformLocation("attenuationProduct"), gLight.attenuation);

  glUniform1i(m_currentShader->GetUniformLocation("gSampler"), 0);

  // Render the objects
  //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->GetBoard().GetModel()));
  //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_world->GetBall().GetModel()));
  
  /*
  glUniform4f(m_currentShader->GetUniformLocation("lightPos"), 2,5,-5,1);
  glUniform4f(m_currentShader->GetUniformLocation("ambientProduct"), ambientMod,ambientMod,ambientMod,1);
  glUniform4f(m_currentShader->GetUniformLocation("diffuseProduct"), .25,.25,.25,1);
  glUniform4f(m_currentShader->GetUniformLocation("specularProduct"), 1,1,1,1);
  glUniform1f(m_currentShader->GetUniformLocation("shine"), 50);
  */

  m_world->Render(m_modelMatrix, 't');//render board
  
  /*
  glUniform4f(m_currentShader->GetUniformLocation("lightPos"), 0,2,0,0);
  glUniform4f(m_currentShader->GetUniformLocation("ambientProduct"), .75,.75, .75 ,1);
  glUniform4f(m_currentShader->GetUniformLocation("diffuseProduct"), .25,.25,.25,1);
  glUniform4f(m_currentShader->GetUniformLocation("specularProduct"), 1,1,1,1);
  glUniform1f(m_currentShader->GetUniformLocation("shine"), .0005);
  glUniform1f(m_currentShader->GetUniformLocation("ball"), 1.0);
  */
  m_world->Render(m_modelMatrix, 'b'); //render ball
  //glUniform1f(m_currentShader->GetUniformLocation("ball"), 0.0);
  
  /*
  glUniform4f(m_currentShader->GetUniformLocation("lightPos"), 0,2,0,0);
  glUniform4f(m_currentShader->GetUniformLocation("ambientProduct"), .75,.75, .75 ,1);
  glUniform4f(m_currentShader->GetUniformLocation("diffuseProduct"), cylDiffMod,cylDiffMod,cylDiffMod,1);
  glUniform4f(m_currentShader->GetUniformLocation("specularProduct"), cylSpecMod,cylSpecMod,cylSpecMod,1);
  glUniform1f(m_currentShader->GetUniformLocation("shine"), 10);
  */
  m_world->Render(m_modelMatrix, 'f'); //render flippers
  
  /*
  glUniform4f(m_currentShader->GetUniformLocation("lightPos"), 0,2,0,0);
  glUniform4f(m_currentShader->GetUniformLocation("ambientProduct"), .75,.75, .75 ,1);
  glUniform4f(m_currentShader->GetUniformLocation("diffuseProduct"), .25,.25,.25,1);
  glUniform4f(m_currentShader->GetUniformLocation("specularProduct"), 1,1,1,1);
  glUniform1f(m_currentShader->GetUniformLocation("shine"), 10);
  */
  m_world->Render(m_modelMatrix, 'c');//render cylinder
  
 

  //cout << "finished rendering objects" << endl;

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
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

void Graphics::moveFlipper(char input)
{
    switch(input)
    {
        case 'w':
            m_world -> moveFlipperUp();
            break;
        case 's':
            m_world -> moveFlipperDown();
            break;
        case 'a':
            m_world -> moveFlipperLeft();
            break;
        case 'd':
            m_world -> moveFlipperRight();
            break;
        default:
            break;
    }
}

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
    ambientMod += .05;
}

void Graphics::decreaseBrightness()
{
    ambientMod -= .05;
}

void Graphics::increaseCylSpecDiff()
{
    cylSpecMod += .05;
    cylDiffMod += .05;
}

void Graphics::decreaseCylSpecDiff()
{
    cylSpecMod -= .05;
    cylDiffMod -= .05;
    
}


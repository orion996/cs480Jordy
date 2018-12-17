#include "shadow.h"

Shadow::Shadow()
{

}

Shadow::~Shadow()
{

}

void Shadow::Initialize()
{
  // Generate depth map FBO
  glGenFramebuffers(1, &m_depthMapFBO);

  // Create depth map texture
  glGenTextures(1, &m_depthMap);
  glBindTexture(GL_TEXTURE_2D, m_depthMap);
  glTexImage2D(
    GL_TEXTURE_2D, 
    0, 
    GL_DEPTH_COMPONENT, 
    m_shadowWidth, 
    m_shadowHeight,
    0,
    GL_DEPTH_COMPONENT,
    GL_FLOAT,
    NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  // Attach depth map texture as FBO's depth buffer
  glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
  glFramebufferTexture2D(
    GL_FRAMEBUFFER,
    GL_DEPTH_ATTACHMENT,
    GL_TEXTURE_2D,
    m_depthMap,
    0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  // Reset to default frame buffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::Update()
{

}

void Shadow::Bind(Shader& shader)
{
//   cout << "SHADOW BIND ENTRY" << endl;

  /*
  glm::mat4 lightMatrix = m_lightProjection * m_lightView;
//   cout << "projection: " << glm::to_string(m_lightProjection) << endl;
//   cout << "view: " << glm::to_string(m_lightView) << endl;
  GLint lightMatrixLocation = shader.GetUniformLocation("lightSpaceMatrix");
  //cout << glm::to_string(lightMatrix) << endl;
  glUniformMatrix4fv(
    lightMatrixLocation, 
    1, 
    GL_FALSE, 
    glm::value_ptr(lightMatrix));
  */

  glViewport(0, 0, m_shadowWidth, m_shadowHeight);
  glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D, m_depthMap); 

//   cout << "SHADOW BIND EXIT" << endl;
}

void Shadow::Reset()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Shadow::GetDepthMap()
{
  return m_depthMap;
}

void Shadow::SetLightProjection(glm::mat4 lightProjection)
{
  m_lightProjection = lightProjection;
}

void Shadow::SetLightView(glm::mat4 lightView)
{
  m_lightView = lightView;
}
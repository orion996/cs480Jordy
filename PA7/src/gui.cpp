#include "gui.h"
#include "engine.h"
#include "camera.h"
#include "planet.h"
GUI::GUI(Camera * _camera, Planet * _planet[9], int _width, int _height):camera(_camera) , width(_width),  height(_height)
{
  for(int i = 0; i<9 ; i++){
      planet[i] = _planet[i];}
}

GUI::~GUI()
{
  ImGui::DestroyContext();
}

bool GUI::Initialize(SDL_Window* window, SDL_GLContext context)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

 	ImGui_ImplSDL2_InitForOpenGL(window, context);
 	ImGui_ImplOpenGL3_Init("#version 330");

 	return true;
}

void GUI::Update(SDL_Window* window, Graphics* graphics)
{

    glm::vec4 v = camera->GetProjection() * camera->GetView() * planet[0]->GetModel() * glm::vec4(0,0,0,1.0);
    v /= v.w;
    v += glm::vec4(1,1,1,1);

     bool buttonPressed = false;
   	ImGui_ImplOpenGL3_NewFrame();
   	ImGui_ImplSDL2_NewFrame(window);
   	ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImVec2 (width, height));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
    ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);
    for(int i = 0; i < 9 ; i++) {
        glm::vec4 v = camera->GetProjection() * camera->GetView() * planet[i]->GetModel() * glm::vec4(0, 0, 0, 1.0);
        //if (i == 0) cout << v.x << ", " << v.y << ", " << v.z << endl;
        if (v.z > 0)
        {
          v /= v.w;
          v += glm::vec4(1, 1, 1, 1);
          ImGui::SetCursorPos(ImVec2(v.x * width / 2.0, height - v.y * height / 2.0));
          if(i == 0) {
              ImGui::Text("Mercury");
              //cout << v.x << endl;
          }
          if(i == 1) {
              ImGui::Text("Venus");
          }
          if(i == 2) {
              ImGui::Text("Earth");
          }
          if(i == 3) {
              ImGui::Text("Mars");
          }
          if(i == 4) {
              ImGui::Text("Jupiter");
          }
          if(i == 5) {
              ImGui::Text("Saturn");
          }
          if(i == 6) {
              ImGui::Text("Uranus");
          }
          if(i == 7) {
              ImGui::Text("Neptune");
          }
          if(i == 8) {
              ImGui::Text("Pluto");
          }
        }
    }


     ImGui::End();
     ImGui::PopStyleColor(1);

  if (ImGui::Begin("HUD", NULL))
  {
    string textMode, textSimSpeed;
    string *textObjectName = new string();

    //set text for mode and object name
    textMode = "Camera Mode: ";
    *textObjectName = "Name: ";
    switch(graphics->GetCameraMode())
    {
      case 0:
        textMode += "Focus";
        switch (graphics->GetFocusedObject())
        {
          case 0:
            *textObjectName += "The Sun";
            break;
          case 1:
            *textObjectName += "Mercury";
            break;
          case 2:
            *textObjectName += "Venus";
            break;
          case 3:
            *textObjectName += "Earth";
            break;
          case 4:
            *textObjectName += "Mars";
            break;
          case 5:
            *textObjectName += "Jupiter";
            break;
          case 6:
            *textObjectName += "Saturn";
            break;
          case 7:
            *textObjectName += "Uranus";
            break;
          case 8:
            *textObjectName += "Neptune";
            break;
          case 9:
            *textObjectName += "Pluto";
            break;
          default: 
            break;
        }
        break;
      case 1:
        textMode += "Free";
        break;
      case 2:
        textMode += "Overview";
        break;
      default:
        break;
    }

    //set text for simulation speed
    sprintf(&textSimSpeed[0], "Simulation Speed: %d", graphics->GetSimulationSpeed());

    //display text
    ImGui::Text(textMode.c_str());
    ImGui::Text(textSimSpeed.c_str());
    if (graphics->GetCameraMode() == MODE_FOCUS)
    {
      ImGui::Separator();
      ImGui::Text(textObjectName->c_str());
    }

    delete textObjectName;
  }
  ImGui::End();

}

void GUI::Render(SDL_Window* window, SDL_GLContext context)
{
  ImGui::Render();
  //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO& io = ImGui::GetIO(); (void)io;
  SDL_GL_MakeCurrent(window, context);
  glViewport(0,0,(int)io.DisplaySize.x, (int)io.DisplaySize.y);
  //glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#include "gui.h"

GUI::GUI()
{
  
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
    //bool buttonPressed = false;

  	ImGui_ImplOpenGL3_NewFrame();
  	ImGui_ImplSDL2_NewFrame(window);
  	ImGui::NewFrame();

    if (ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoResize));
    {
      if (ImGui::Button("Play/Pause Planet"))
      {
        if (graphics->IsPlanetPaused())
        {
          graphics->SetPlanetPaused(0);
        }
        else
        {
          graphics->SetPlanetPaused(1);
        }
      }
      if (ImGui::Button("Change Orbit Direction"))
      {
        if (graphics->GetPlanetOrbit() == 0)
        {
          graphics->SetPlanetOrbit(1);
        }
        else
        {
          graphics->SetPlanetOrbit(0);
        }
      }
      if (ImGui::Button("Change Spin Direction"))
      {
        if (graphics->GetPlanetSpin() == 0)
        {
          graphics->SetPlanetSpin(1);
        }
        else
        {
          graphics->SetPlanetSpin(0);
        }
      }

      ImGui::Separator();

      ImGui::Text("Info");

      if (graphics->IsPlanetPaused())
      {
        ImGui::Text("Paused");
      }
      else
      {
        ImGui::Text("Playing");
      }

      if (graphics->GetPlanetOrbit() == 0)
      {
        ImGui::Text("Planet Orbit Direction: Clockwise");
      }
      else
      {
        ImGui::Text("Planet Orbit Direction: Counter-Clockwise");
      }

      if (graphics->GetPlanetSpin() == 0)
      {
        ImGui::Text("Planet Spin Direction: Clockwise");
      }
      else
      {
        ImGui::Text("Planet Spin Direction: Counter-Clockwise");
      }

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
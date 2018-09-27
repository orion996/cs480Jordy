#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_gui;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  m_graphics->SetObjectFilename(m_objectFilename);
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Start the GUI
  m_gui = new GUI();
  if (!m_gui->Initialize(m_window->GetWindow(), m_window->GetContext()))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    //bool guiClicked = false;

    // Update the DT
    m_DT = getDT();

    while(SDL_PollEvent(&m_event) != 0)
    {
      if (!ImGui::IsMouseHoveringAnyWindow())
      {
        //ImGui_ImplSDL2_ProcessEvent(&m_event)
        Keyboard();
      }
      //else
      {
        
      }
      //Keyboard();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_graphics->Render();

    // Update and render the GUI
    //m_gui->Update(m_window->GetWindow(), m_graphics);
    //m_gui->Render(m_window->GetWindow(), m_window->GetContext());

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN || m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
    else if (m_event.key.keysym.sym == SDLK_SPACE || m_event.button.button == SDL_BUTTON_MIDDLE)
    {
      //cout << "space pressed" << endl;
      if (m_graphics->IsPlanetPaused())
      {
        m_graphics->SetPlanetPaused(false);
        //cout << "PLAY" << endl;
      }
      else
      {
        m_graphics->SetPlanetPaused(true);
        //cout << "PAUSE" << endl;
      }
    }
    else if (m_event.button.button == SDL_BUTTON_RIGHT)
    {
      if (m_graphics->GetPlanetOrbit() == 1)
      {
        m_graphics->SetPlanetOrbit(0);
        //cout << "ORBIT: COUNTER-CLOCKWISE" << endl;
      }
      else
      {
        m_graphics->SetPlanetOrbit(1);
        //cout << "ORBIT: CLOCKWISE" << endl;
      }
    }
    else if (m_event.key.keysym.sym == SDLK_LEFT)
    {
      m_graphics->SetPlanetOrbit(0);
      //cout << "ORBIT: COUNTER-CLOCKWISE" << endl;
    }
    else if (m_event.key.keysym.sym == SDLK_RIGHT)
    {
      m_graphics->SetPlanetOrbit(1);
      //cout << "ORBIT: CLOCKWISE" << endl;
    }
    else if (m_event.button.button == SDL_BUTTON_LEFT)
    {
      if (m_graphics->GetPlanetSpin() == 1)
      {
        m_graphics->SetPlanetSpin(0);
        //cout << "SPIN: COUNTER-CLOCKWISE" << endl;
      }
      else
      {
        m_graphics->SetPlanetSpin(1);
        //cout << "SPIN: CLOCKWISE" << endl;
      }
    }
    else if (m_event.key.keysym.sym == SDLK_a)
    {
      m_graphics->SetPlanetSpin(0);
      //cout << "SPIN: COUNTER-CLOCKWISE" << endl;
    }
    else if (m_event.key.keysym.sym == SDLK_d)
    {
      m_graphics->SetPlanetSpin(1);
      //cout << "SPIN: CLOCKWISE" << endl;
    }
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}

void Engine::SetObjectFilename(string objectFilename)
{
  m_objectFilename = objectFilename;
}

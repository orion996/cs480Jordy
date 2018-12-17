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

int Engine:: getHeight(){
    return m_WINDOW_HEIGHT;
}

int Engine:: getWidth(){
    return m_WINDOW_WIDTH;
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
    if (m_graphics->m_world->isGameOver())
    {
      // Update the DT
      m_DT = getDT();

      while(SDL_PollEvent(&m_event) != 0) {} //clear events

      m_graphics->Update(m_DT);
      m_graphics->Render();

      // Update and render the GUI
      m_gui->SetGameOver(true);
      m_running = m_gui->Update(m_window->GetWindow(), m_graphics);
      m_gui->Render(m_window->GetWindow(), m_window->GetContext());

      // Swap to the Window
      m_window->Swap();
    }
    else
    {
      // Update the DT
      m_DT = getDT();

      while(SDL_PollEvent(&m_event) != 0)
      {
        Keyboard();
      }
    
      // Update and render the graphics
      m_graphics->Update(m_DT);
      m_graphics->Render();

      // Update and render the GUI
      m_gui->SetGameOver(false);
      m_gui->Update(m_window->GetWindow(), m_graphics);
      m_gui->Render(m_window->GetWindow(), m_window->GetContext());

      // Swap to the Window
      m_window->Swap();
    }
  }
}

void Engine::Keyboard()
{
  
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else
  {
  	switch (m_event.type)
  	{
  		case SDL_KEYDOWN:
  			switch (m_event.key.keysym.sym)
  			{
  				case SDLK_ESCAPE:
  					m_running = false;
            //generateScores();
  					break;
          case SDLK_w:
            m_graphics->m_camera->HandleKeyboardInput("w", true);
            //m_graphics->increaseDiffuse();
            break;
          case SDLK_a:
            m_graphics->m_camera->HandleKeyboardInput("a", true);
            break;
          case SDLK_s:
            m_graphics->m_camera->HandleKeyboardInput("s", true);
            //m_graphics->decreaseDiffuse();
            break;
          case SDLK_d:
            m_graphics->m_camera->HandleKeyboardInput("d", true);
            break;
          case SDLK_UP:
            m_graphics->m_camera->HandleKeyboardInput("up", true);
            break;
          case SDLK_DOWN:
            m_graphics->m_camera->HandleKeyboardInput("down", true);
            break;
          case SDLK_LEFT:
            m_graphics->m_camera->HandleKeyboardInput("left", true);
            break;
          case SDLK_RIGHT:
            m_graphics->m_camera->HandleKeyboardInput("right", true);
            break;
          case SDLK_m:
            m_graphics->m_camera->Reset();
            if (m_graphics->m_camera->GetMode() == MODE_GAME)
            {
              m_graphics->m_camera->SetMode(MODE_FREE);
            }
            else
            {
              m_graphics->m_camera->SetMode(MODE_GAME);
            }
            break;
          case SDLK_TAB:
            m_graphics->ChangeLightIndex();
            break;
          case SDLK_1:
            m_graphics->decreaseSpecular(0);
            break;
          case SDLK_2:
            m_graphics->increaseSpecular(0);
            break;
          case SDLK_3:
            m_graphics->decreaseSpecular(1);
            break;
          case SDLK_4:
            m_graphics->increaseSpecular(1);
            break;
          case SDLK_5:
            m_graphics->decreaseSpecular(2);
            break;
          case SDLK_6:
            m_graphics->increaseSpecular(2);
            break;
          case SDLK_7:
            m_graphics->decreaseSpecular(3);
            break;
          case SDLK_8:
            m_graphics->increaseSpecular(3);
            break;
          case SDLK_9:
            m_graphics->decreaseSpecular(4);
            break;
          case SDLK_0:
            m_graphics->increaseSpecular(4);
            break;
          case SDLK_MINUS:
            m_graphics->decreaseBrightness();
            break;
          case SDLK_EQUALS:
            m_graphics->increaseBrightness();
            break;
          case SDLK_LEFTBRACKET:
            m_graphics->decreaseDiffuse();
            break;
          case SDLK_RIGHTBRACKET:
            m_graphics->increaseDiffuse();
            break;
          case SDLK_PERIOD:
            m_graphics->increaseSpotLightRadius();
            break;
          case SDLK_COMMA:
            m_graphics->decreaseSpotLightRadius();
            break;
          case SDLK_LSHIFT:
            m_graphics->m_world->FlipLeft();
            break;
          case SDLK_RSHIFT:
            m_graphics->m_world->FlipRight();
            break;
          case SDLK_RETURN:
            //pull plunger
            m_graphics->m_world->PullPlunger();
            break;
          case SDLK_SPACE:
            m_graphics->changeShader();
            break; 
          default:
            break;
        }
        break;
      case SDL_KEYUP:
        switch(m_event.key.keysym.sym)
        {
          case SDLK_w:
            m_graphics->m_camera->HandleKeyboardInput("w", false);
            break;
          case SDLK_a:
            m_graphics->m_camera->HandleKeyboardInput("a", false);
            break;
          case SDLK_s:
            m_graphics->m_camera->HandleKeyboardInput("s", false);
            break;
          case SDLK_d:
            m_graphics->m_camera->HandleKeyboardInput("d", false);
            break;
          case SDLK_UP:
            m_graphics->m_camera->HandleKeyboardInput("up", false);
            break;
          case SDLK_DOWN:
            m_graphics->m_camera->HandleKeyboardInput("down", false);
            break;
          case SDLK_LEFT:
            m_graphics->m_camera->HandleKeyboardInput("left", false);
            break;
          case SDLK_RIGHT:
            m_graphics->m_camera->HandleKeyboardInput("right", false);
            break;
          case SDLK_RETURN:
            //release plunger
            m_graphics->m_world->ReleasePlunger();
            break;
          default:
            break;
        }
        break;			
  		default:
  			break;
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

void Engine::generateScores()
{
    ifstream fin, topFin;
    fin.open("..//assets//scoreLog.txt");
    topFin.open("..//assets//topScores.txt");
    
    struct TopPlayer
    {
      int score;
      string name;
    };
    
    int score = 0;
    
    TopPlayer leaderBoard[11];
    
    while(!fin.eof())
        fin >> score;
    
    cout << endl << "YOUR SCORE: " << score << endl;
    
    for(int i=0 ; i<10 ; i++)
    {
       topFin >> leaderBoard[i].score >> leaderBoard[i].name;
       //cout << leaderBoard[i].score << " " << leaderBoard[i].name << endl;
    }

    string str;
    cout << "Please Enter Your Name: ";
    cin >> str;

    leaderBoard[10].score = score;
    leaderBoard[10].name = str;

    
    //topScores.push_back(score);
    
    ofstream fout;
    fout.open("..//assets//topScores.txt");

    //**SORT**

    TopPlayer temp;
    for(int i=0 ; i<11 ; i++)
    {
      for(int j=i+1 ; j<11 ; j++)
      {
        if(leaderBoard[i].score < leaderBoard[j].score)
        {
          //swap
          temp = leaderBoard[i];
          leaderBoard[i] = leaderBoard[j];
          leaderBoard[j] = temp;
        }
      }
    }

    //********
    
    int rank = 1;
    cout << endl << "**TOP SCORES**" << endl;
    for(int i=0; i<10 ; i++)
    {
        cout << rank++ << ") " << leaderBoard[i].score << " " << leaderBoard[i].name << endl;
        fout << leaderBoard[i].score << " " << leaderBoard[i].name << endl; 
    }
        
    fin.close();
    topFin.close();
    fout.close();
}
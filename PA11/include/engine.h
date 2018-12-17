#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "gui.h"
#include "graphics.h"
#include "world.h"
#include <time.h>
#include <algorithm>
#include <vector>

class Engine
{
  public:
    Engine(string name, int width, int height);
    Engine(string name);
    ~Engine();

    bool Initialize();
    void Run();
    void Keyboard();

    int getHeight();
    int getWidth();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    
    //void generateScores();

  private:
    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    bool m_FULLSCREEN;
    SDL_Event m_event;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    GUI *m_gui;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;

    clock_t m_startTime;
    int m_timeLeft;
    int m_gameTime = 120; //seconds
    bool justGameOver = false;

    int state = 0;
};

#endif // ENGINE_H
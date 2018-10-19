#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "gui.h"
#include "graphics.h"

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

    void SetObjectFilename(string objectFilename);

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

    string m_objectFilename;
};

#endif // ENGINE_H

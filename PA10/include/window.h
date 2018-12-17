#ifndef WINDOW_H
#define WINDOW_H

//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
using namespace std;

class Window
{
  public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
    void Swap();

    SDL_Window* GetWindow();
    SDL_GLContext GetContext();

  private:
    SDL_Window* gWindow;
    SDL_GLContext gContext;
};

#endif /* WINDOW_H */

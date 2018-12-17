#ifndef WINDOW_H
#define WINDOW_H

//#include "imgui.h"
//#include "imgui_impl_sdl.h"
//#include "imgui_impl_opengl3.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "sound.h"
#include "graphics_headers.h"
using namespace std;
class Sound;
class Window
{
  public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
    void Swap();

    SDL_Window* GetWindow();
    SDL_GLContext GetContext();

    Sound * t;
  private:

    SDL_Window* gWindow;
    SDL_GLContext gContext;
};

#endif /* WINDOW_H */

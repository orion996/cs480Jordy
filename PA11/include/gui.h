#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace std;

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "graphics_headers.h"
#include "window.h"
#include "graphics.h"

class GUI
{
public:
  
	GUI();
	~GUI();

	int Initialize(SDL_Window* window, SDL_GLContext context);
	bool Update(SDL_Window* window, Graphics* graphics);
	void Render();

  ImVec2 CalculateCenteredPos(ImVec2 textSize);

  void SetGameOver(bool gameOver);
  void SetTimeLeft(int timeLeft);

private:

  ImFont* m_fontSmall;
  ImFont* m_fontMed;
  ImFont* m_fontBig;

  int m_width;
  int m_height;
  int m_timeLeft = 999;
  bool m_gameOver = false;
	
};

#endif /* GUI_H */
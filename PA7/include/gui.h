#ifndef GUI_H
#define GUI_H

#include <iostream>
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
	GUI(Camera * camera, Planet * planet[9], int height, int width);
	~GUI();

	bool Initialize(SDL_Window* window, SDL_GLContext context);
	void Update(SDL_Window* window, Graphics* graphics);
	void Render(SDL_Window* window, SDL_GLContext context);
	Camera * camera;
	Planet * planet[9];
	int height, width;
private:
	
};

#endif /* GUI_H */
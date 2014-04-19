#include <iostream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	
	//window we're rendering to
	SDL_Window* window = NULL;

	//the surface contained by the window
	SDL_Surface* screen_surface = NULL;

	//initialise sdl
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		string error_message = "SDL could not initialise: \n\t";
		error_message += SDL_GetError();
		throw runtime_error(error_message);
	}

	//create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL) {
		string error_message = "SDL window could not be created: \n\t";
		error_message += SDL_GetError();
		throw runtime_error(error_message);
	}

	//get window surface
	screen_surface = SDL_GetWindowSurface(window);

	//fill it white
	SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0x0, 0x0));

	//update the window surface
	SDL_UpdateWindowSurface(window);

	//wait
	SDL_Event evt;
	bool program_running = true;
	while(program_running)
	{
		SDL_WaitEvent(&evt);
		if(evt.type == SDL_QUIT)
			program_running = false;
	}

	//destroy window
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

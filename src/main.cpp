#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* g_window = NULL;
SDL_Surface* g_screen_surface = NULL;
map<int, SDL_Surface*> g_key_press_surfaces;
int g_current_surface = -1;


void init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw runtime_error(SDL_GetError());
	}

	g_window = SDL_CreateWindow("SDL Tutorial - Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == NULL) {
		throw runtime_error(SDL_GetError());
	}

	g_screen_surface = SDL_GetWindowSurface(g_window);

	return;
}

SDL_Surface* loadSurface(string path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());

	if (loadedSurface == NULL) {
		throw runtime_error(SDL_GetError());
	}

	return loadedSurface;
}

void loadMedia() {
	g_key_press_surfaces[-1] = loadSurface("press.bmp");
	g_key_press_surfaces[SDLK_UP] = loadSurface("up.bmp");
	g_key_press_surfaces[SDLK_DOWN] = loadSurface("down.bmp");
	g_key_press_surfaces[SDLK_LEFT] = loadSurface("left.bmp");
	g_key_press_surfaces[SDLK_RIGHT] = loadSurface("right.bmp");

	return;
}

void close() {
	for(map<int, SDL_Surface*>::iterator it = g_key_press_surfaces.begin(); it != g_key_press_surfaces.end(); ++it) {
		SDL_FreeSurface(it->second);
		it->second = NULL;
	}
	
	SDL_DestroyWindow(g_window); //also handles destruction of screen surface
	g_window = NULL;
	g_screen_surface = NULL;

	SDL_Quit();
}




int main(int argc, char* args[]) {
	init();
	loadMedia();

	SDL_Event event;
	bool program_running = true;
	while(program_running) {
		SDL_BlitSurface(g_key_press_surfaces[g_current_surface], NULL, g_screen_surface, NULL);
		SDL_UpdateWindowSurface(g_window);

		SDL_WaitEvent(&event); //preferable to poll event - uses basically no CPU
		if(event.type == SDL_QUIT) {
			program_running = false;
		}

		else if(event.type == SDL_KEYDOWN) {
			if(g_key_press_surfaces.find(event.key.keysym.sym) != g_key_press_surfaces.end()) {
				g_current_surface = event.key.keysym.sym;
			}
		}

		else if(event.type == SDL_KEYUP) {
			if(g_key_press_surfaces.find(event.key.keysym.sym) != g_key_press_surfaces.end()) {
				g_current_surface = -1;
			}
		}
	}

	close();

	return 0;
}

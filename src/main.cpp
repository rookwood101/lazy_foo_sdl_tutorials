#include <iostream>
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* g_window = NULL;
SDL_Surface* g_screen_surface = NULL;
SDL_Surface* g_hello_world = NULL;

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

void loadMedia() {
	g_hello_world = SDL_LoadBMP("hello_world.bmp");

	if(g_hello_world == NULL) {
		throw runtime_error(SDL_GetError());
	}

	return;
}

void close() {
	SDL_FreeSurface(g_hello_world);
	g_hello_world = NULL;

	SDL_DestroyWindow(g_window); //also handles destruction of screen surface
	g_window = NULL;
	g_screen_surface = NULL;

	SDL_Quit();
}

int main(int argc, char* args[]) {
	init();
	loadMedia();

	SDL_BlitSurface(g_hello_world, NULL, g_screen_surface, NULL);
	SDL_UpdateWindowSurface(g_window);

	SDL_Event event;
	bool program_running = true;
	while(program_running) {
		SDL_WaitEvent(&event); //preferable to poll event - uses basically no CPU
		if(event.type == SDL_QUIT)
			program_running = false;
	}

	close();

	return 0;
}

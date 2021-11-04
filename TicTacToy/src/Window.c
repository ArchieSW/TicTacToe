#include "pch.h"
#include "Window.h"


Window* create_new_window(char* title, int width, int height, Color color) {
	Window* new_window = (Window*)malloc(sizeof(Window));
	if (!new_window) {
		printf("[ERROR]: MEMORY ALLOCATION ERROR\n");
		return NULL;
	}
	SDL_Window* window = NULL;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("[ERROR]: FAILED TO CREATE NEW WINDOW\n");
		printf(SDL_GetError());
		return NULL;
	}
	
	new_window->window = window;
	new_window->width = width;
	new_window->height = height;
	new_window->title = title;
	
	SDL_Surface* background = NULL;
	background = SDL_GetWindowSurface(new_window->window);
	SDL_FillRect(background, NULL, SDL_MapRGB(background->format, color.red, color.green, color.blue));
	
	new_window->background = background;
	
	return new_window;
}


void free_window(Window* window) {
	SDL_DestroyWindow(window->window);
	free(window);
};
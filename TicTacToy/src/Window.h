#pragma once
#include "pch.h"
#include "Color.h"
typedef struct Window {
	SDL_Window* window;
	char* title;
	SDL_Surface* background;
	int width;
	int height;
} Window;

Window* create_new_window(char* title, int width, int height, Color color);
void free_window(Window* window);
#pragma once
#include "pch.h"
#include "Window.h"
#include "GameData.h"
typedef struct Image {
	char* path;
	SDL_Surface* image_surface;
	SDL_Rect* image_data;
	PlaceState state;
} Image;

Image* create_new_image(int x, int y, char* path);
void free_image(Image* image);
void glue_image(Image* image, Window* win);

#pragma once
#include "pch.h"
#include "Image.h"


Image* create_new_image(int x, int y, char* path) {
	Image* img = (Image*)malloc(sizeof(Image));
	
	if (!img) {
		printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
		return NULL;
	}
	
	img->image_surface = SDL_LoadBMP(path);
	
	if (!(img->image_surface)) {
		printf("[ERROR]: FAILED TO LOAD IMAGE\n");
		free(img);
		return NULL;
	}
	
	SDL_Rect* data = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	
	if (!data) {
		printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
		SDL_FreeSurface(img->image_surface);
		free(img);
		return NULL;
	}

	data->x = x;
	data->y = y;
	data->w = img->image_surface->w;
	data->h = img->image_surface->h;

	img->image_data = data;
	return img;
}


void free_image(Image* image) {
	SDL_FreeSurface(image->image_surface);
	free(image->image_data);
	free(image);
}


void glue_image(Image* image, Window* win) {
	SDL_BlitSurface(image->image_surface, NULL, win->background, image->image_data);
}
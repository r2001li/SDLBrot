#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

typedef struct {
	SDL_Renderer *renderer;
	int startY;
	int endY;
	double centerX;
	double centerY;
	double zoom;
} ThreadData;

int renderThread(void *arg);

void renderMandelbrot(SDL_Renderer *renderer, double centerX, double centerY, double zoom);

#endif

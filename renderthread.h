#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

typedef struct {
	int x;
	int y;
	int r;
	int g;
	int b;
} RenderPoint;

typedef struct {
	SDL_Renderer *renderer;
	RenderPoint *buffer;
	int startY;
	int endY;
	double centerX;
	double centerY;
	double zoom;
} ThreadData;

int renderThread(void *arg);

void renderMandelbrot(SDL_Renderer *renderer, double centerX, double centerY, double zoom);

#endif

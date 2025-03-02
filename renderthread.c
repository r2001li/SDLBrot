#include <SDL2/SDL.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_thread.h>
#include "app.h"
#include "mandelbrot.h"
#include "renderthread.h"

SDL_mutex *renderMutex;

int renderThread(void *arg) {
	ThreadData *data = (ThreadData*)arg;

	SDL_Renderer *renderer = data->renderer;
	int startY = data->startY;
	int endY = data->endY;
	double centerX = data->centerX;
	double centerY = data->centerY;
	double zoom = data->zoom;

        for (int py = startY; py < endY; py++) {
		for (int px = 0; px < WIDTH; px++) {
			// Map pixel to complex plane
			double x0 = centerX + (px - WIDTH / 2.0) * 4.0 / (zoom * WIDTH);
			double y0 = centerY + (py - HEIGHT / 2.0) * 4.0 / (zoom * HEIGHT);

			// Iteration
			int iteration = iterate(x0, y0);

			// Coloring
			double t = (double)iteration / MAX_ITER;
			int r = (int)(9 * (1 - t) * t * t * t * 255);
			int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
			int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
			
			/*
			int color = (iteration * 255) / MAX_ITER;
			SDL_SetRenderDrawColor(m_renderer, color, color, color, 255);
			*/

			// Draw point
			SDL_LockMutex(renderMutex);
			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			SDL_RenderDrawPoint(renderer, px, py);
			SDL_UnlockMutex(renderMutex);
		}
	}

	return 0;
}

void renderMandelbrot(SDL_Renderer *renderer, double centerX, double centerY, double zoom) {
	SDL_Thread *threads[NUM_THREADS];
	ThreadData threadData[NUM_THREADS];
	int rowsPerThread = HEIGHT / NUM_THREADS;
	renderMutex = SDL_CreateMutex();

	// Create threads
	for (int i = 0; i < NUM_THREADS; i++) {
		threadData[i].renderer = renderer;
		threadData[i].startY = i * rowsPerThread;
		threadData[i].endY = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * rowsPerThread;
		threadData[i].centerX = centerX;
		threadData[i].centerY = centerY;
		threadData[i].zoom = zoom;

		threads[i] = SDL_CreateThread(renderThread, "RenderThread", (void*)&threadData[i]);
		if (!threads[i]) {
			printf("Thread creation failed! SDL Error: %s\n", SDL_GetError());
		}
	}

	// Wait for threads
	for (int i = 0; i < NUM_THREADS; i++) {
		SDL_WaitThread(threads[i], NULL);
	}

	// Present image
	SDL_RenderPresent(renderer);
	SDL_DestroyMutex(renderMutex);
}


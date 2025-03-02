#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "app.h"
#include "renderthread.h"

int main(int argc, char *argv[]) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *m_window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (!m_window) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	
	if (!m_renderer) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return 1;
	}

	// Mandelbrot set rendering
	double centerX = -0.5, centerY = 0.0, zoom = 1.0;
	// renderMandelbrot(m_renderer, centerX, centerY, zoom);

	SDL_Event event;
	int quit = 0;
	int needsDraw = 1;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			} else if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y > 0) {
					zoom *= 1.1;
					needsDraw = 1;
				} else if (event.wheel.y < 0) {
					zoom /= 1.1;
					needsDraw = 1;
				}

				// renderMandelbrot(m_renderer, centerX, centerY, zoom);
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						centerX -= 0.1 / zoom;
						needsDraw = 1;
						break;
					case SDLK_RIGHT:
						centerX += 0.1 / zoom;
						needsDraw = 1;
						break;
					case SDLK_UP:
						centerY -= 0.1 / zoom;
						needsDraw = 1;
						break;
					case SDLK_DOWN:
						centerY += 0.1 / zoom;
						needsDraw = 1;
						break;
				}

				//renderMandelbrot(m_renderer, centerX, centerY, zoom);
			}
		}

		if (needsDraw) {
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 225);
			SDL_RenderClear(m_renderer);
			renderMandelbrot(m_renderer, centerX, centerY, zoom);
			needsDraw = 0;
		}

		SDL_Delay(10);
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

	return 0;
}


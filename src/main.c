#include "defs.h"
#include "draw.h"
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

void init_sdl(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Window *window;
	SDL_Surface *surface;

	// Setting x and y pos to SDL_WINDOW_POS_UNDEFINED leaves window positioning
	// upto the OS
	window = SDL_CreateWindow(
		"Renderer", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, 
		SDL_WINDOW_RESIZABLE
	);

	if (window == NULL) {
		printf("Unable to open window.");
		exit(EXIT_FAILURE);
	}

	surface = SDL_GetWindowSurface(window);

	if (surface == NULL) {
		printf("Unable to get the window surface!");
		exit(EXIT_FAILURE);
	}
	
	draw_line(surface);
	SDL_UpdateWindowSurface(window);
	/* SDL_DestroyWindow(window); */
}

void do_input(void) {
	SDL_Event event;

	// Handle all events sequentially. Puts event data to SDL_Event pointer.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;

			default:
				break;
		}
	}
}

void cleanup(void) {
	// Handle application closing
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	// As name suggests, initialize SDL.
	init_sdl();
	atexit(cleanup);

	// Main "game" loop.
	while (1) {
		do_input();
	}

	return EXIT_SUCCESS;
}

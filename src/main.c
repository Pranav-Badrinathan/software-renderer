#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void init_sdl(void) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Setting x and y pos to SDL_WINDOW_POS_UNDEFINED leaves window positioning
	// upto the OS
	SDL_Window *window = SDL_CreateWindow("Renderer", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 600, 480, 0);

	if (window == NULL) {
		printf("Unable to open window.");
		exit(EXIT_FAILURE);
	}
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

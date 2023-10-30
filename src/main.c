#include "defs.h"
#include "linalg.h"
#include "draw.h"
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

void draw_cube(SDL_Surface *surface) {
	struct Triangle cube[12] = {
		(struct Triangle) {(struct Vec3){0, 0, 0}, (struct Vec3){0, 1, 0}, (struct Vec3){1, 1, 0}},
		(struct Triangle) {(struct Vec3){0, 0, 0}, (struct Vec3){1, 1, 0}, (struct Vec3){1, 0, 0}},

		(struct Triangle) {(struct Vec3){1, 0, 0}, (struct Vec3){1, 1, 0}, (struct Vec3){1, 1, 1}},
		(struct Triangle) {(struct Vec3){1, 0, 0}, (struct Vec3){1, 1, 1}, (struct Vec3){1, 0, 1}},

		(struct Triangle) {(struct Vec3){1, 0, 1}, (struct Vec3){1, 1, 1}, (struct Vec3){0, 1, 1}},
		(struct Triangle) {(struct Vec3){1, 0, 1}, (struct Vec3){0, 1, 1}, (struct Vec3){0, 0, 1}},

		(struct Triangle) {(struct Vec3){0, 0, 1}, (struct Vec3){0, 1, 1}, (struct Vec3){0, 1, 0}},
		(struct Triangle) {(struct Vec3){0, 0, 1}, (struct Vec3){0, 1, 0}, (struct Vec3){0, 0, 0}},

		(struct Triangle) {(struct Vec3){0, 1, 0}, (struct Vec3){0, 1, 1}, (struct Vec3){1, 1, 1}},
		(struct Triangle) {(struct Vec3){0, 1, 0}, (struct Vec3){1, 1, 1}, (struct Vec3){1, 1, 0}},

		(struct Triangle) {(struct Vec3){1, 0, 1}, (struct Vec3){0, 0, 1}, (struct Vec3){0, 0, 0}},
		(struct Triangle) {(struct Vec3){1, 0, 1}, (struct Vec3){0, 0, 0}, (struct Vec3){1, 0, 0}},
	};

	struct Mat4x4 proj = get_proj_matrix();

	for (int i = 0; i < 12; i++) {
		struct Triangle t;
		for (int j = 0; j < 3; j++) {
			cube[i].verts[j].z += 3.0f;

			t.verts[j] = matrix_vec3_mul(proj, cube[i].verts[j]);

			t.verts[j] = vector_add(t.verts[j], (struct Vec3){1, 1, 0});
			
			t.verts[j].x *= 0.5f * (float)SCREEN_WIDTH;
			t.verts[j].y *= 0.5f * (float)SCREEN_HEIGHT;

			printf("x: %f, y: %f\n", t.verts[j].x, t.verts[j].y);
		}

		draw_triangle(surface, t);
	}
}

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
	
	SDL_LockSurface(surface);

	draw_cube(surface);
	
	SDL_UnlockSurface(surface);
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

#include "input.h"
#include <stdlib.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <stdint.h>

const uint8_t KEY_JUST_PRESSED = 0x01;
const uint8_t KEY_HELD = 0x02;
const uint8_t KEY_JUST_RELEASED = 0x04;

uint8_t keys[SDL_NUM_SCANCODES] = { 0 };

bool key_just_pressed(int scode) {
	return keys[scode] & KEY_JUST_PRESSED;
}

bool key_held(int scode) {
	return keys[scode] & KEY_HELD;
}

bool key_just_released(int scode) {
	return keys[scode] & KEY_JUST_RELEASED;
}

void update_input(void) {
	SDL_Event event;

	// Clear previous frame's frams-specific inputs. Leave persistent.
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		keys[i] &= ~(KEY_JUST_PRESSED | KEY_JUST_RELEASED);
	}

	// Handle all events sequentially. Puts event data to SDL_Event pointer.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
				break;

			case SDL_KEYDOWN:
					keys[event.key.keysym.scancode] |= KEY_JUST_PRESSED | KEY_HELD;
				break;

			case SDL_KEYUP:
					keys[event.key.keysym.scancode] |= KEY_JUST_RELEASED;
					keys[event.key.keysym.scancode] &= ~KEY_HELD;
				break;

			default:
				break;
		}
	}
}


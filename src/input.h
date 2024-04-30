#ifndef SREND_INPUT_H_
#define SREND_INPUT_H_

#include <stdbool.h>

// Handle all the input polling once. Needs to be called per frame.
void update_input(void);

// returns true if the Key corresponding to the SDL Scancode provided was
// released this frame.
bool key_just_released(int scode);

// returns true if the Key corresponding to the SDL Scancode provided is held
// down this frame.
bool key_held(int scode);

// returns true if the Key corresponding to the SDL Scancode provided starts
// being pressed down this frame.
bool key_just_pressed(int scode);

#endif

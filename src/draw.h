#ifndef SREND_DRAW_H_
#define SREND_DRAW_H_

#include <SDL2/SDL_surface.h>

// STRUCTS

struct Point { int x; int y; };

struct Triangle { struct Point verts[3]; };

// END STRUCTS

/*
 * Sets the pixel at (x, y) to the given pixel value.
 * NOTE: Remember to lock the surface before calling this!
 */
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


/*
 * Return the pixel value at (x, y)
 * NOTE: Remember to lock the surface before calling this!
 */
Uint32 get_pixel(SDL_Surface *surface, int x, int y);


void draw_line(SDL_Surface *surface, struct Point p1, struct Point p2);

void draw_triangle(SDL_Surface *surface, struct Triangle tri);

#endif // SREND_DRAW_H_

#include "draw.h"
#include "defs.h"
#include <stdbool.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int bpp = surface->format->BytesPerPixel;

	// Address of the pixel to retrieve. surface->pixels is a pointer. So any 
	// math is pointer arithmetic.
	// Get the poiter to the memory location of the first pixel. Then add the
	// row number (y) multiplied by the number of bytes in one row (pitch).
	// Finally, add the x offset with x * bpp, to get the location of pixel.
	Uint8 *p = (Uint8 *) surface->pixels + (y * surface->pitch) + (x * bpp);

	switch (bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
        	} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
        	}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	
	// Same process as in put_pixel. Check there for a detailed comment.
	Uint8 *p = (Uint8 *) surface->pixels + (y * surface->pitch) + (x * bpp);

	switch (bpp) {
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		//shouldn't happen, but avoids warnings

		default:
			return 0;
	}
}

void draw_line(SDL_Surface *surface, struct Vec4 p1, struct Vec4 p2) {
	const int dx = p2.x - p1.x;
	const int dy = p2.y - p1.y;

	const int adx = abs(dx);
	const int ady = abs(dy);

	int x = p1.x;
	int y = p1.y;
	
	if (adx >= ady) { // Case when the slope <= 1
		int descision = 2 * ady - adx;
	
		for (int i = 0; i < adx; i++) {
			if ((0 < x && x < (SCREEN_WIDTH)) && (0 < y && y < SCREEN_HEIGHT)) {
				put_pixel(surface,
				 x,
				 y,
				 SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
			}
			// Plus if the slope is positive, minus if negative.
			x = dx < 0 ? x - 1 : x + 1;

			if (descision <= 0) {
				descision += 2 * ady;
			} else {
				descision += (2 * ady) - (2 * adx);
				// Plus if the slope is positive, minus if negative.
				y = dy < 0 ? y - 1 : y + 1;
			}
		}
	} else { // When slope > 1
		int descision = 2 * adx - ady;

		for (int i = 0; i < ady; i++) {
			if ((0 < x && x < (SCREEN_WIDTH)) && (0 < y && y < SCREEN_HEIGHT)) {
				put_pixel(surface,
				 x,
				 y,
				 SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
			}
			y = dy < 0 ? y - 1 : y + 1;

			if (descision <= 0) {
				descision += 2 * adx;
			} else {
				descision += (2 * adx) - (2 * ady);
				x = dx < 0 ? x - 1 : x + 1;
			}
		}
	}
}

void draw_triangle(SDL_Surface *surface, struct Triangle tri) {
	draw_line(surface, tri.verts[0], tri.verts[1]);
	draw_line(surface, tri.verts[1], tri.verts[2]);
	draw_line(surface, tri.verts[2], tri.verts[0]);
}

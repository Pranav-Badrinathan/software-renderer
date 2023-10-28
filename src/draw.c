#include "draw.h"
#include "defs.h"
#include <SDL2/SDL_surface.h>

void draw_line(SDL_Surface *surface) {
	put_pixel(surface, 
		   SCREEN_WIDTH / 2, 
		   SCREEN_HEIGHT / 2, 
		   SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));
}

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
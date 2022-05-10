#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct _Coord {
	int x, y;
} Coord;

static inline SDL_Color mk_SDL_Color(int r, int g, int b, int a) {
	SDL_Color const c = { r, g, b, a };
	return c;
}

#endif

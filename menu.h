#ifndef _MENU_H_
#define _MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdlib.h>

#define FONT_COLOR		0xFFFCF9
#define SHADOW_COLOR	0x000000

#define BAR_H 14
#define BAR_BORDER 2

#define TOTAL_ENTRIES 19
#define ELEMENTS_PADDING 3

#define NORM_COLOR 0x010101FF
#define SEL_COLOR 0xCC0000FF

#define WIN_DEFAULT_W	800
#define WIN_DEFAULT_H	600

#define UNHEX(color) \
    ((color) >> (8 * 3)) & 0xFF, \
    ((color) >> (8 * 2)) & 0xFF, \
    ((color) >> (8 * 1)) & 0xFF, \
    ((color) >> (8 * 0)) & 0xFF

typedef struct Entry {
	char *text;
	bool selected;
	size_t index;
} Entry;

void select_prev(Entry []);
void select_next(Entry []);
void draw_entry(SDL_Renderer *, TTF_Font *, int, int, Entry);

#endif

#ifndef _MENU_H_
#define _MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

#define FONT_COLOR		0xFFFCF9
#define SHADOW_COLOR	0x000000

#define BAR_H 14
#define BAR_BORDER 2

#define TOTAL_ENTRIES 19
#define ELEMENTS_PADDING 3

#define NORM_COLOR 0x010101FF
#define SEL_COLOR 0xEE0000FF
#define HOVER_COLOR 0x444444FF

#define WIN_DEFAULT_W	800
#define WIN_DEFAULT_H	600

#define UNHEX(color) \
    ((color) >> (8 * 3)) & 0xFF, \
    ((color) >> (8 * 2)) & 0xFF, \
    ((color) >> (8 * 1)) & 0xFF, \
    ((color) >> (8 * 0)) & 0xFF

typedef struct Entry {
	char *text;
	bool selected, hover;
	size_t index;
	Coord pos;
} Entry;

void select_prev(Entry *);
void select_next(Entry *);
void select_index(Entry *, size_t i);
void draw_entry(SDL_Renderer *, TTF_Font *, int, int, const Entry);

void Entry_new(Entry *);
size_t entry_at(Entry *, int, int);
void hover_at(Entry *, int, int);
void hover_entry(Entry *, size_t);
void compute_entries_pos(Entry *, int, int);


#endif

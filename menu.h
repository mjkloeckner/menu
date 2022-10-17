#ifndef _MENU_H_
#define _MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "util.h"

#define FONT_COLOR		0xFFFCF9FF
#define SHADOW_COLOR	0x000000FF

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

typedef struct {
	char *text;
	bool selected, hover;
	size_t index;
	Coord pos;
} Elem;

typedef struct {
	Elem **elements;
	size_t size;
} Set;

void Set_new(Set **, size_t size);
void Set_draw(Set *);
void Set_destroy(Set *);

void Set_select_prev(Set *);
void Set_select_next(Set *);
void Set_select_index(Set *, size_t i);
void Set_hover_at(Set *, int, int);
void Set_hover_elem(Set *, size_t);
size_t Set_elem_at(Set *, int, int);
void Set_compute_pos(Set *, int, int);


/* void Elem_new(Elem **); */
/* void Elem_destroy(Elem *); */

void Elem_draw(SDL_Renderer *, TTF_Font *, int, int, const Elem *);
void Elem_set_text(Elem *, const char *);



#endif

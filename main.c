#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "menu.h"

#define FONT_SIZE	12
#define FONT_NAME	"./VictorMono-Bold.ttf"

#define WIN_DEFAULT_W	800
#define WIN_DEFAULT_H	600

#define BG_COLOR	0x323232FF

static char *elements_text[TOTAL_ENTRIES] = {
	"Bubble sort",
	"Bubble sort (improved)",
	"Insertion sort",
	"Binary insertion sort",
	"Merge sort",
	"Quick sort",
	"Quick sort (dual pivots)",
	"Quick sort (LR pointers)",
	"Quick sort (LL pointers)",
	"Shell sort",
	"Radix sort",
	"Heap sort",
	"Cocktail shaker sort",
	"Gnome sort",
	"Odd-even sort",
	"Tim sort",
	"Bogo sort",
	"Stooge sort",
	"Spaghetti sort"
};

int win_w, win_h;
TTF_Font *font;
int x, y;
Uint32 buttons;

/* TODO: remove global variables */
/* TODO: custom box size, margin, padding, pos, etc */
/* TODO: linked list (?) */

int main (void)
{
	SDL_Window *win;
	SDL_Renderer *rend;
	int min_w, min_h;
	size_t i;
	Set *set;

	SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow(
		"menu",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_DEFAULT_W,
		WIN_DEFAULT_H,
		SDL_WINDOW_RESIZABLE
    );

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!win || !rend) return 1;
	else if(TTF_Init() == -1) return 1;

	font = TTF_OpenFont(FONT_NAME, FONT_SIZE);

	min_h = (TOTAL_ENTRIES * (BAR_H + ELEMENTS_PADDING)) + ELEMENTS_PADDING;
	min_w = (((float)min_h * 4) / 3);
	SDL_SetWindowMinimumSize(win, min_w, min_h);

	bool run = true;
	SDL_Event event;
	win_w = WIN_DEFAULT_W;
	win_h = WIN_DEFAULT_H;

	Set_new(&set, TOTAL_ENTRIES);

	for(i = 0; i < set->size; i++)
		Elem_set_text(set->elements[i], elements_text[i]);

	SDL_Keymod mod;
	size_t index = TOTAL_ENTRIES;
	while(run) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					run = false;
					break;
				default: break;
			case SDL_KEYDOWN:
				/* printf("SDL_GetModState() == %X\n", SDL_GetModState()); */
				mod = SDL_GetModState();
				switch(event.key.keysym.scancode) {
					case SDL_SCANCODE_Q:
						run = false;
						break;
					case SDL_SCANCODE_J:
					case SDL_SCANCODE_DOWN:
						if(mod == KMOD_NONE) Set_select_next(set);
						break;
					case SDL_SCANCODE_K:
					case SDL_SCANCODE_UP:
						if(mod == KMOD_NONE) Set_select_prev(set);
						break;
					case SDL_SCANCODE_RETURN:
						for(i = 0; i < TOTAL_ENTRIES; i++)
							if(set->elements[i]->selected)
								printf("%s\n", set->elements[i]->text);
						break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				index = Set_elem_at(set, event.button.x, event.button.y);
				if(index != TOTAL_ENTRIES) {
					printf("%s\n", set->elements[index]->text);
					Set_select_index(set, index);
				}
				break;
			case SDL_WINDOWEVENT:
				switch(event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					/* printf("INFO: window resized to: %dx%d\n", win_w, win_h); */
					win_w = event.window.data1;
					win_h = event.window.data2;
					break;
				default: break;
				}
				break;
			}
		}

		SDL_PumpEvents();  /* make sure we have the latest mouse state. */

		buttons = SDL_GetMouseState(&x, &y);
		Set_hover_at(set, x, y);

		SDL_SetRenderDrawColor(rend, UNHEX(BG_COLOR));
		SDL_RenderClear(rend);

		Set_compute_pos(set, win_w, win_h);
		for(i = 0; i < TOTAL_ENTRIES; i++)
			Elem_draw(rend, font, win_w, win_h, set->elements[i]);

		SDL_RenderPresent(rend);
		SDL_Delay(1);
	}

	TTF_CloseFont(font);

	SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

	TTF_Quit();
	SDL_Quit();
	return 0;
}

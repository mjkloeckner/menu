#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "menu.h"

#define FONT_SIZE	12
#define FONT_NAME	"/home/mk/.local/share/fonts/VictorMono-Bold.ttf"

#define WIN_DEFAULT_W	800
#define WIN_DEFAULT_H	600

int win_w, win_h;
TTF_Font *font;

int main (void) {
	SDL_Window *win;
	SDL_Renderer *rend;
	size_t i;

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

	bool run = true;
	SDL_Event event;
	win_w = WIN_DEFAULT_W;
	win_h = WIN_DEFAULT_H;

	Entry entries[TOTAL_ENTRIES] = {0};

	for(i = 0; i < TOTAL_ENTRIES; i++) {
		entries[i].selected = false;
		entries[i].index = i;
	}

	entries[0].text = "Bubble sort";
	entries[1].text = "Bubble sort (improved)";
	entries[2].text = "Insertion sort";
	entries[3].text = "Binary insertion sort";
	entries[4].text = "Merge sort";
	entries[5].text = "Quick sort";
	entries[6].text = "Quick sort (dual pivots)";
	entries[7].text = "Quick sort (LR pointers)";
	entries[8].text = "Quick sort (LL pointers)";
	entries[9].text = "Shell sort";
	entries[10].text = "Radix sort";
	entries[11].text = "Heap sort";
	entries[12].text = "Cocktail shaker sort";
	entries[13].text = "Gnome sort";
	entries[14].text = "Odd-even sort";
	entries[15].text = "Tim sort";
	entries[16].text = "Bogo sort";
	entries[17].text = "Stooge sort";
	entries[18].text = "Spaghetti sort";

	entries[0].selected = true;
	SDL_Keymod mod;
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
					case SDL_SCANCODE_J:
					case SDL_SCANCODE_DOWN:
						if(mod == KMOD_NONE) select_next(entries);
						break;
					case SDL_SCANCODE_K:
					case SDL_SCANCODE_UP:
						if(mod == KMOD_NONE) select_prev(entries);
						break;
					case SDL_SCANCODE_RETURN:
						for(i = 0; i < TOTAL_ENTRIES; i++)
							if(entries[i].selected)
								printf("%s\n", entries[i].text);
						break;
					default: break;
				}
				break;
			case SDL_WINDOWEVENT:
				switch(event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					win_w = event.window.data1;
					win_h = event.window.data2;
					break;
				default: break;
				}
				break;
			}
		}

		SDL_SetRenderDrawColor(rend, 32, 32, 32, 0);
		SDL_RenderClear(rend);

		for(i = 0; i < TOTAL_ENTRIES; i++)
			draw_entry(rend, font, win_w, win_h, entries[i]);

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

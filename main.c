#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE	12
#define FONT_NAME	"/home/mk/.local/share/fonts/VictorMono-Bold.ttf"
#define FONT_COLOR	0xFFFCF9
#define SHADOW_COLOR	0x000000

#define BAR_H 14
#define BAR_BORDER 2

#define TOTAL_ENTRIES 6
#define ELEMENTS_PADDING 3

#define NORM_COLOR 0x010101FF
#define SEL_COLOR 0xCC0000FF

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

void next_selection(Entry entries[]) {
	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].selected == true) {
			entries[i].selected = false;
			if((i + 1) < TOTAL_ENTRIES)
				entries[i + 1].selected = true;
			else
				entries[0].selected = true;

			return;
		}
	}
}

void prev_selection(Entry entries[]) {
	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].selected == true) {
			entries[i].selected = false;
			if(i == 0) entries[TOTAL_ENTRIES - 1].selected = true;
			else entries[i - 1].selected = true;

			return;
		}
	}
}

int win_w, win_h;
int text_w, text_h;
TTF_Font *font;

void draw_entry(SDL_Renderer *rend, Entry entry) {
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Rect text_rect, text_container;
	SDL_Color text_color, text_color_shadow;

	text_color_shadow.r = (char)(SHADOW_COLOR >> 16) & 0xFF;
	text_color_shadow.g = (char)(SHADOW_COLOR >> 8) & 0xFF;
	text_color_shadow.b = (char)(SHADOW_COLOR) & 0xFF;

	text_color.r = (char)(FONT_COLOR >> 16) & 0xFF;
	text_color.g = (char)(FONT_COLOR >> 8) & 0xFF;
	text_color.b = (char)(FONT_COLOR) & 0xFF;

	text_container.x = BAR_BORDER;

	text_container.y = (win_h / 2) - (((BAR_H * TOTAL_ENTRIES) + (ELEMENTS_PADDING * (TOTAL_ENTRIES - 1))) / 2) + BAR_H + (entry.index * (ELEMENTS_PADDING + BAR_H));

	text_container.w = win_w - (BAR_BORDER * 2);
	text_container.h = -BAR_H;

	if(entry.selected)
		SDL_SetRenderDrawColor(rend, UNHEX(SEL_COLOR)); /* RGBA */
	else
		SDL_SetRenderDrawColor(rend, UNHEX(NORM_COLOR)); /* RGBA */

	SDL_RenderFillRect(rend, &text_container);

	if(entry.selected) {
		text_surface = TTF_RenderText_Blended(font, entry.text, text_color_shadow);
		text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

		TTF_SizeText(font, entry.text, &text_w, &text_h);

		text_rect.x = (win_w / 2) - (text_w / 2) + 1;
		text_rect.y = (win_h / 2) - (((BAR_H * TOTAL_ENTRIES) + (ELEMENTS_PADDING * (TOTAL_ENTRIES - 1))) / 2) + BAR_H + (entry.index * (ELEMENTS_PADDING + BAR_H)) - (BAR_H + 1) + 1;
		text_rect.w = text_surface->w;
		text_rect.h = text_surface->h;

		SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
		SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text_surface);

		text_surface = TTF_RenderText_Blended(font, entry.text, text_color);
		text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

		TTF_SizeText(font, entry.text, &text_w, &text_h);

		text_rect.x = (win_w / 2) - (text_w / 2);
		text_rect.y = (win_h / 2) - (((BAR_H * TOTAL_ENTRIES) + (ELEMENTS_PADDING * (TOTAL_ENTRIES - 1))) / 2) + BAR_H + (entry.index * (ELEMENTS_PADDING + BAR_H)) - (BAR_H + 1);
		text_rect.w = text_surface->w;
		text_rect.h = text_surface->h;
	}
	else {
		text_surface = TTF_RenderText_Blended(font, entry.text, text_color);
		text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

		TTF_SizeText(font, entry.text, &text_w, &text_h);

		text_rect.x = (win_w / 2) - (text_w / 2);
		text_rect.y = (win_h / 2) - (((BAR_H * TOTAL_ENTRIES) + (ELEMENTS_PADDING * (TOTAL_ENTRIES - 1))) / 2) + BAR_H + (entry.index * (ELEMENTS_PADDING + BAR_H)) - (BAR_H + 1);
		text_rect.w = text_surface->w;
		text_rect.h = text_surface->h;
	}
	SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
}


int main (void) {
	SDL_Window *win;
	SDL_Renderer *rend;

	SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow(
		"menu",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_RESIZABLE
    );

	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!win || !rend)
		return 1;
	else if(TTF_Init() == -1)
		return 1;

	font = TTF_OpenFont(FONT_NAME, FONT_SIZE);

	bool run = true;
	SDL_Event event;
	win_w = 800;
	win_h = 600;

	Entry entries[TOTAL_ENTRIES] = {0};

	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		entries[i].selected = false;
		entries[i].index = i;
	}

	entries[0].text = "Bubble sort";
	entries[1].text = "Bubble sort (improved)";
	entries[2].text = "Insertion sort";
	entries[3].text = "Merge sort";
	entries[4].text = "Quick sort";
	entries[5].text = "Shell sort";

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
				switch(event.key.keysym.scancode) {
				case SDL_SCANCODE_TAB:
					mod = SDL_GetModState();
					if((mod == KMOD_LSHIFT) || (mod == KMOD_RSHIFT)) {
						prev_selection(entries);
						break;
					} else
						next_selection(entries);
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

		for(int i = 0; i < TOTAL_ENTRIES; i++)
			draw_entry(rend, entries[i]);

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

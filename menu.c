#include "menu.h"

/* Finds the selected entry then selects next */
void select_next(Entry entries[]) {
	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].selected == true) {
			entries[i].selected = false;
			if((i + 1) < TOTAL_ENTRIES) entries[i + 1].selected = true;
			else entries[0].selected = true;
			return;
		}
	}
}

/* Finds the selected entry then selects previous */
void select_prev(Entry entries[]) {
	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].selected == true) {
			entries[i].selected = false;
			if(i == 0) entries[TOTAL_ENTRIES - 1].selected = true;
			else entries[i - 1].selected = true;
			return;
		}
	}
}

void draw_entry(SDL_Renderer *rend, TTF_Font *font, int win_w, int win_h, Entry entry) {
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Rect text_rect, box;
	SDL_Color text_color, text_color_shadow;
	int first_entry_y_pos, win_center_y;
	int text_w, text_h;

	win_center_y = (win_h / 2);
	first_entry_y_pos = win_center_y -
		((((BAR_H + ELEMENTS_PADDING) * TOTAL_ENTRIES) - ELEMENTS_PADDING) / 2) +
		BAR_H + (entry.index * (ELEMENTS_PADDING + BAR_H));

	text_color_shadow.r = (char)(SHADOW_COLOR >> 16) & 0xFF;
	text_color_shadow.g = (char)(SHADOW_COLOR >> 8) & 0xFF;
	text_color_shadow.b = (char)(SHADOW_COLOR) & 0xFF;

	text_color.r = (char)(FONT_COLOR >> 16) & 0xFF;
	text_color.g = (char)(FONT_COLOR >> 8) & 0xFF;
	text_color.b = (char)(FONT_COLOR) & 0xFF;

	box.x = BAR_BORDER;
	box.y = first_entry_y_pos;
	box.w = win_w - (BAR_BORDER * 2);
	box.h = -BAR_H;

	SDL_SetRenderDrawColor(rend, UNHEX(entry.selected ? SEL_COLOR : NORM_COLOR));

	SDL_RenderFillRect(rend, &box);
	TTF_SizeText(font, entry.text, &text_w, &text_h);

	/* Draw shadow */
	if(entry.selected) {
		text_surface = TTF_RenderText_Blended(font, entry.text, text_color_shadow);
		text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

		text_rect.x = (win_w / 2) - (text_w / 2) + 2;
		text_rect.y = first_entry_y_pos - (BAR_H + 1) + 2;
		text_rect.w = text_surface->w;
		text_rect.h = text_surface->h;

		SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
		SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text_surface);
	}

	text_surface = TTF_RenderText_Blended(font, entry.text, text_color);
	text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

	text_rect.x = (win_w / 2) - (text_w / 2);
	text_rect.y = first_entry_y_pos - (BAR_H + 1);
	text_rect.w = text_surface->w;
	text_rect.h = text_surface->h;

	SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
}


#include "menu.h"

/* Finds the selected entry then selects next */
void select_next(Entry *entries) {
	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].selected == true) {
			entries[i].selected = false;
			if((i + 1) == TOTAL_ENTRIES) entries[0].selected = true;
			else entries[i + 1].selected = true;
			i++;
			continue;
		}
		entries[i].selected = false;
	}
}

/* Finds the selected entry then selects previous */
void select_prev(Entry *entries) {
	for(int i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].selected == true) {
			entries[i].selected = false;
			if(i == 0) {
				entries[TOTAL_ENTRIES - 1].selected = true;
				break;
			}
			else entries[i - 1].selected = true;
		}
	}
}

void select_index(Entry *entries, size_t index) {
	size_t i;
	for(i = 0; i < TOTAL_ENTRIES; i++) {
		if(entries[i].index == index) entries[i].selected = true;
		else if(entries[i].selected == true) entries[i].selected = false;
	}
}

size_t entry_at(Entry *entries, int x, int y) {
	size_t i;

	for(i = 0; i < TOTAL_ENTRIES; i++)
		if((y < entries[i].pos.y) && (y > (entries[i].pos.y - BAR_H)))
			return i;

	return TOTAL_ENTRIES;
}

void compute_entries_pos(Entry *entries, int win_w, int win_h) {
	int first_entry_pos_y, win_center_y;
	size_t i;

	win_center_y = (win_h / 2);
	first_entry_pos_y = win_center_y -
		((((BAR_H + ELEMENTS_PADDING) * TOTAL_ENTRIES) - ELEMENTS_PADDING) / 2) + BAR_H;

	for(i = 0; i < TOTAL_ENTRIES; i++) {
		entries[i].pos.x = BAR_BORDER;
		entries[i].pos.y = (first_entry_pos_y + (entries[i].index * (ELEMENTS_PADDING + BAR_H)));
	}
}

void hover_entry(Entry *entries, size_t index) {
	size_t i;

	for(i = 0; i < TOTAL_ENTRIES; i++)
		entries[i].hover = ((i == index) ? true : false);
}

void hover_at(Entry *entries, int x, int y) {
	size_t i;

	for(i = 0; i < TOTAL_ENTRIES; i++) {
		if((y < entries[i].pos.y) && (y > (entries[i].pos.y - BAR_H)))
			entries[i].hover = true;
		else entries[i].hover = false;
	}
}

void draw_entry(SDL_Renderer *rend, TTF_Font *font, int win_w, int win_h, const Entry entry) {
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Rect text_rect, box;
	SDL_Color text_color, text_color_shadow;
	int text_w, text_h;

	text_color = mk_SDL_Color(UNHEX(FONT_COLOR));
	text_color_shadow = mk_SDL_Color(UNHEX(SHADOW_COLOR));

	box = (SDL_Rect){ BAR_BORDER, entry.pos.y, win_w - (BAR_BORDER * 2), -BAR_H };

	SDL_SetRenderDrawColor(rend, UNHEX(entry.selected ? SEL_COLOR : (entry.hover ? HOVER_COLOR : NORM_COLOR)));
	SDL_RenderFillRect(rend, &box);

	TTF_SizeText(font, entry.text, &text_w, &text_h);

	/* Draw shadow */
	if(entry.selected) {
		text_surface = TTF_RenderText_Blended(font, entry.text, text_color_shadow);
		text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

		text_rect.x = (win_w / 2) - (text_w / 2) + 2;
		text_rect.y = entry.pos.y - (BAR_H + 1) + 2;
		text_rect.w = text_surface->w;
		text_rect.h = text_surface->h;

		SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
		SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text_surface);
	}

	text_surface = TTF_RenderText_Blended(font, entry.text, text_color);
	text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

	text_rect.x = (win_w / 2) - (text_w / 2);
	text_rect.y = entry.pos.y - (BAR_H + 1);
	text_rect.w = text_surface->w;
	text_rect.h = text_surface->h;

	SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
}

#include "menu.h"

/* Finds the selected entry then selects next */
void Set_select_next(Set *set) {
	for(int i = 0; i < set->size; i++) {
		if(set->elements[i]->selected == true) {
			set->elements[i]->selected = false;
			if((i + 1) == set->size) set->elements[0]->selected = true;
			else set->elements[i + 1]->selected = true;
			i++;
			continue;
		}
		set->elements[i]->selected = false;
	}
}

/* Finds the selected entry then selects previous */
void Set_select_prev(Set *set) {
	for(int i = 0; i < set->size; i++) {
		if(set->elements[i]->selected == true) {
			set->elements[i]->selected = false;
			if(i == 0) {
				set->elements[set->size - 1]->selected = true;
				break;
			}
			else set->elements[i - 1]->selected = true;
		}
	}
}

void Set_select_index(Set *set, size_t index) {
	size_t i;
	for(i = 0; i < set->size; i++) {
		if(set->elements[i]->index == index) set->elements[i]->selected = true;
		else if(set->elements[i]->selected == true) set->elements[i]->selected = false;
	}
}

size_t Set_elem_at(Set *set, int x, int y) {
	size_t i;

	for(i = 0; i < set->size; i++)
		if((y < set->elements[i]->pos.y) && (y > (set->elements[i]->pos.y - BAR_H)))
			return i;

	return set->size;
}

void Set_compute_pos(Set *set, int win_w, int win_h) {
	int first_entry_pos_y, win_center_y;
	size_t i;

	win_center_y = (win_h / 2);
	first_entry_pos_y = win_center_y -
		((((BAR_H + ELEMENTS_PADDING) * set->size) - ELEMENTS_PADDING) / 2) + BAR_H;

	for(i = 0; i < set->size; i++) {
		set->elements[i]->pos.x = BAR_BORDER;
		set->elements[i]->pos.y = (first_entry_pos_y + (set->elements[i]->index * (ELEMENTS_PADDING + BAR_H)));
	}
}

void Set_hover_elem(Set *set, size_t index) {
	size_t i;

	for(i = 0; i < set->size; i++)
		set->elements[i]->hover = ((i == index) ? true : false);
}

void Set_hover_at(Set *set, int x, int y) {
	size_t i;

	for(i = 0; i < set->size; i++) {
		if((y < set->elements[i]->pos.y) && (y > (set->elements[i]->pos.y - BAR_H)))
			set->elements[i]->hover = true;
		else set->elements[i]->hover = false;
	}
}

void Elem_draw(SDL_Renderer *rend, TTF_Font *font, int win_w, int win_h, const Elem *elem) {
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Rect text_rect, box;
	SDL_Color text_color, text_color_shadow;
	int text_w, text_h;

	text_color = mk_SDL_Color(UNHEX(FONT_COLOR));
	text_color_shadow = mk_SDL_Color(UNHEX(SHADOW_COLOR));

	box = (SDL_Rect) { BAR_BORDER, elem->pos.y, win_w - (BAR_BORDER * 2), -BAR_H };

	SDL_SetRenderDrawColor(rend, UNHEX(elem->selected ? SEL_COLOR : (elem->hover ? HOVER_COLOR : NORM_COLOR)));
	SDL_RenderFillRect(rend, &box);

	TTF_SizeText(font, elem->text, &text_w, &text_h);

	/* Draw shadow */
	if(elem->selected) {
		text_surface = TTF_RenderText_Blended(font, elem->text, text_color_shadow);
		text_texture = SDL_CreateTextureFromSurface(rend, text_surface);

		text_rect.x = (win_w / 2) - (text_w / 2) + 2;
		text_rect.y = elem->pos.y - (BAR_H + 1) + 2;
		text_rect.w = text_surface->w;
		text_rect.h = text_surface->h;

		SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
		SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text_surface);
	}

	text_surface = TTF_RenderText_Blended(font, elem->text, text_color);
	text_texture = SDL_CreateTextureFromSurface(rend, text_surface);
	text_rect.x = (win_w / 2) - (text_w / 2);
	text_rect.y = elem->pos.y - (BAR_H + 1);
	text_rect.w = text_surface->w;
	text_rect.h = text_surface->h;

	SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(text_surface);
}

void Set_new(Set **set, size_t size) {
	if(size == 0) return;

	(*set) = malloc(sizeof(Set));

	if((*set) == NULL)
		return;

	if(((*set)->elements = malloc(sizeof(Elem) * size)) == NULL)
		return;

	for(size_t i = 0; i < size; i++)
		if(((*set)->elements[i] = malloc(sizeof(Elem))) == NULL)
			return;

	/* Initialize elements */
	(*set)->size = size;
	for(size_t i = 0; i < size; i++) {
		(*set)->elements[i]->text = NULL;
		(*set)->elements[i]->selected = false;
		(*set)->elements[i]->hover = false;
		(*set)->elements[i]->index = i;
	}

	(*set)->elements[0]->selected = true;
}

void Set_destroy(Set *set) {
	free(set->elements);
	free(set);
}

void Elem_set_text(Elem *el, const char *src) {
	size_t text_len = strlen(src);

	el->text = calloc(text_len + 1, sizeof(char));

	strcpy(el->text, src);
}

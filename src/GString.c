#include "GString.h"
struct GString_Data {
	SDL_Texture 	*texture;
	unsigned long	text_buffer;
	SDL_Rect 	text_box;
	SDL_Rect 	char_box;
};

Fontman Fontman__Init(GE mainGE, char *font_path, size_t font_size, double ratio, SDL_Color color)
{
	Fontman self;

	self.data = malloc(sizeof(*(self.data)));

	// These lines are actually useless, maybe I (should) remove them later!
	self.font_size = font_size;
	self.ratio = ratio;
	self.data->color = color; 

	self.data->font = TTF_OpenFont(font_path, font_size); get_error(self.data->font);
	char alphanumerics[65+1] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789: !";
	SDL_Surface *tmp_surfaces = TTF_RenderText_Solid(self.data->font, alphanumerics, color); get_error(tmp_surfaces);
	self.data->texture = SDL_CreateTextureFromSurface(mainGE.Renderer, tmp_surfaces); get_error(self.data->texture);
	SDL_FreeSurface(tmp_surfaces);
	self.char_rect = (SDL_Rect) {0, 0, self.font_size * self.ratio, self.font_size};


	return self;
}

void Fontman__Destroy(Fontman self)
{
	SDL_DestroyTexture(self.data->texture);
	free(self.data);
}

void GString__RenderCopy(GString self)
{
	char index; 
	int x_limit = self.data->text_box.x, y_limit = self.data->text_box.y;
	SDL_Rect char_box = self.data->char_box;
	for (int i = 0; self.string[i]; i++) {
		char_box.x += self.fontman.font_size * self.fontman.ratio;
		index = self.string[i];
		// A pseudo-binary search based on ASCII table
		if (self.string[i] >= 'a') 
			index -= 'a';
		else if (self.string[i] >= 'A')
			index -= 'A' - 26;
		else if (self.string[i] >= '0')
			index -= '0' - 52;
		else if (self.string[i] == '!')
			index = 64; // alphanumerics[64] = '!'
		else
			index = 63; // alphanumerics[63] = ' '
		self.fontman.char_rect.x = self.fontman.font_size * self.fontman.ratio * index;
		SDL_RenderCopy(self.GE.Renderer, self.fontman.data->texture, (const SDL_Rect*) &self.fontman.char_rect ,  (const SDL_Rect*) &char_box);
	} 
	// Useless, isn't it?
	self.fontman.char_rect.x = 0;
}

GString GString__Create(GE mainGE, Fontman fontman, int x, int y, char *string, size_t buffer)
{
	GString self;
	self.GE = mainGE;

	self.data = malloc(sizeof(*(self.data))); get_error(self.data);
	self.fontman = fontman;
	self.data->text_buffer = buffer;
	self.string = malloc(sizeof(*self.string) * self.data->text_buffer); get_error(self.string);
	strncpy(self.string, string, buffer);
	self.data->text_box = (SDL_Rect) {x, y, buffer * self.fontman.font_size * self.fontman.ratio, self.fontman.font_size};
	self.data->char_box = self.data->text_box;
	self.data->char_box.w = self.fontman.font_size * self.fontman.ratio;
	self.data->char_box.h = self.fontman.font_size;

	self.buffer = buffer;

	return self;
}

void GString__Destroy(GString self)
{
	free(self.string);
	free(self.data);
}


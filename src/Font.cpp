#include "globals.h"
#include "Font.h"

Font::Font(const char * filename, int fontSize)
{
	font = TTF_OpenFont(filename, fontSize);
	if (font == nullptr) {
		throw std::runtime_error(TTF_GetError());
	}
}

Font::~Font()
{
    TTF_CloseFont(font);
}

SDL_Texture * Font::makeTexture(SDL_Renderer * renderer, SDL_Color color, const char * text)
{
    SDL_Surface * surface = TTF_RenderText_Blended(font, text, color);
    if (surface == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
    if (texture == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    return texture;
}

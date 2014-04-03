#pragma once

#include "globals.h"

class Font 
{
public:
	Font(const char * filename, int fontSize);
	virtual ~Font();
	SDL_Texture * makeTexture(SDL_Renderer * renderer, SDL_Color color, const char * text);

private:
	TTF_Font * font;
};

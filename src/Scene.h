#pragma once

#include "globals.h"
#include "Font.h"

class Scene 
{
public:
    static void init(SDL_Window * window);
    static void shutdown();
    static void render();
    static void setBackground(const char * filename);
    static void setText(const std::string & text);

private:
    static SDL_Renderer * renderer;
    static SDL_Texture * backgroundTexture;
    static Font * font;
    static SDL_Texture * textTexture;
};

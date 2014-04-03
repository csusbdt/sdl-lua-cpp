#pragma once

#include "globals.h"

class Console
{
public:
    static void init();
    static void onTextInput(const SDL_TextInputEvent & e);
    static bool consumeKeyDown(const SDL_KeyboardEvent & e); // return true to consume 
    static void render(SDL_Renderer * renderer);

private:
    static bool inputtingLuaChunk;
    static std::string luaChunk;
};

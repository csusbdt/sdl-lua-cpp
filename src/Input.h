
#pragma once

#include "globals.h"

class Input
{
public:
    static void init();
    static void processEventQueue();
    static void onQuit();
    static void onKeyDown(const SDL_KeyboardEvent & e);
    static void onMouseDown(const SDL_MouseButtonEvent & e);
    static void onTextInput(const SDL_TextInputEvent & e);

private:
//    static bool inputtingLuaChunk;
//    static std::string luaChunk;
};

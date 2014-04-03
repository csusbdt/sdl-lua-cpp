#include "globals.h"
#include "Lua.h"
#include "Scene.h"
#include "Console.h"
#include "Input.h"

void Input::init() 
{
    if (SDL_IsTextInputActive() == SDL_FALSE) {
        SDL_StartTextInput();
    }
}

void Input::processEventQueue()
{
    SDL_Event e;
    while (!APP_isQuitting() && SDL_PollEvent(&e)) {
        if      (e.type == SDL_QUIT)            onQuit();
        else if (e.type == SDL_KEYDOWN)         onKeyDown(e.key);
        else if (e.type == SDL_MOUSEBUTTONDOWN) onMouseDown(e.button);
        else if (e.type == SDL_TEXTINPUT)       onTextInput(e.text);
    }    
}

void Input::onQuit() 
{
    APP_quit();
}

void Input::onKeyDown(const SDL_KeyboardEvent & e) 
{
    if (Console::consumeKeyDown(e)) return;

    // if (inputtingLuaChunk) {
    //     if (e.keysym.sym == SDLK_ESCAPE) {
    //         inputtingLuaChunk = false;
    //         luaChunk.clear();
    //         Scene::setText(luaChunk);
    //         return;
    //     }
    //     if (e.keysym.sym == SDLK_RETURN) {
    //         if (luaChunk.empty()) {
    //             inputtingLuaChunk = false;
    //             return;
    //         }
    //         // If runChunk returns false, then a RETURN event is coming
    //         // (for a reason I don't understand).  In this case, let the
    //         // coming RETURN event set inputtingLuaChunk to false.
    //         if (Lua::runChunk(luaChunk.c_str())) {
    //             inputtingLuaChunk = false;
    //         }
    //         luaChunk.clear();
    //         Scene::setText(luaChunk);
    //     }
    //     else if (e.keysym.sym == SDLK_BACKSPACE) {
    //         if (luaChunk.size() > 0) {
    //             luaChunk.resize(luaChunk.size() - 1);
    //             Scene::setText(luaChunk);
    //         }
    //     }
    //     else {
    //         // Ignore all other key presses, because they will also 
    //         // come through as text input events for character input.
    //     }
    // }
    // else if (e.keysym.sym == SDLK_RETURN) {
    //     inputtingLuaChunk = true;
    // }
}

void Input::onMouseDown(const SDL_MouseButtonEvent & e) 
{
    if (e.type == SDL_MOUSEBUTTONDOWN) {
    }
}

void Input::onTextInput(const SDL_TextInputEvent & e)
{
    Console::onTextInput(e);
    // if (inputtingLuaChunk) {
    //     luaChunk.append(e.text);
    //     Scene::setText(luaChunk);
    // }
}

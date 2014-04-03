#include "globals.h"
#include "Lua.h"
#include "Scene.h"
#include "Console.h"

bool Console::inputtingLuaChunk = false;
std::string Console::luaChunk;

void Console::init() 
{
    luaChunk.reserve(80);
}

bool Console::consumeKeyDown(const SDL_KeyboardEvent & e) 
{
    if (!inputtingLuaChunk) {
        if (e.keysym.sym == SDLK_RETURN) {
            inputtingLuaChunk = true;
            Scene::setText(luaChunk);
            return true;
        }
        return false;
    }

    if (e.keysym.sym == SDLK_ESCAPE) {
        inputtingLuaChunk = false;
        luaChunk.clear();
        Scene::setText(luaChunk);
    }
    else if (e.keysym.sym == SDLK_BACKSPACE) {
        if (luaChunk.size() > 0) {
            luaChunk.resize(luaChunk.size() - 1);
            Scene::setText(luaChunk);
        }
    }
    else if (e.keysym.sym == SDLK_RETURN) {
        if (luaChunk.empty()) {
            inputtingLuaChunk = false;
            Scene::setText(luaChunk);
        }
        /* runChunk returns false if the chunk fails to run.
           In this case -- and for a reason I don't understand --
           a RETURN event is coming.  In this case, we let the
           coming RETURN event set inputtingLuaChunk to false. */
        else {
            if (Lua::runChunk(luaChunk.c_str())) {
                inputtingLuaChunk = false;
                luaChunk.clear();
                Scene::setText(luaChunk);
            } else {
                luaChunk.clear();
                inputtingLuaChunk = false;
            }
        }
    }
    return true;
}

void Console::onTextInput(const SDL_TextInputEvent & e)
{
    if (inputtingLuaChunk) {
        luaChunk.append(e.text);
        Scene::setText(luaChunk);
    }
}

#include "globals.h"
#include "Lua.h"
#include "Scene.h"
#include "Functions.h"

int Functions::msgbox(lua_State * L)
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 1) {
        return luaL_error(L, "msgbox takes 1 argument");
    }
    const char * msg = luaL_checkstring(L, 1);
    if (msg == nullptr) {
        return luaL_error(L, "msg can not be nil");
    }
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_INFORMATION,
        APP_title,                      
        msg,
        nullptr);
    return 0;
}

int Functions::quit(lua_State * L) 
{
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments != 0) {
        return luaL_error(L, "quit takes no arguments");
    }
    APP_quit();
    return 0;
}

int Functions::setbg(lua_State * L)
{
    const char * filename = nullptr;
    int numberOfArguments = lua_gettop(L);
    if (numberOfArguments > 1) {
        return luaL_error(L, "setbg takes 0 or 1 arguments");
    }
    if (numberOfArguments == 1) {
        filename = luaL_checkstring(L, 1);
    }
    Scene::setBackground(filename);
    return 0;
}

void Functions::init(lua_State * state)
{
    lua_register(state, "msgbox", msgbox);
    lua_register(state, "quit",   quit);
    lua_register(state, "setbg",   setbg);
}

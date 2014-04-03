#include "globals.h"
#include "Functions.h"
#include "Scene.h"
#include "Lua.h"

lua_State * Lua::state = nullptr;

void Lua::throwError(int result)
{
    if (result != LUA_OK) {
        throw std::runtime_error(lua_tostring(state, -1));
    }
}

bool Lua::displayError(int result)
{
    if (result != LUA_OK) {
        Scene::setText(lua_tostring(state, -1));
//        APP_displayError(lua_tostring(state, -1));
        return true;
    }
    else {
        return false;
    }
}

void Lua::doFile(const char * pathname) 
{
    throwError(luaL_loadfile(state, pathname));
    throwError(lua_pcall(state, 0, 0, 0));
}

void Lua::init()
{
    state = luaL_newstate();
    if (state == nullptr) {
        throw new std::runtime_error("Failed to create Lua state.");
    }

    luaL_checkversion(state);

    throwError(lua_gc(state, LUA_GCSTOP, 0)); 

    luaL_openlibs(state);

    Functions::init(state);

    doFile("scripts/main.lua");

    lua_gc(state, LUA_GCRESTART, 0);
}

void Lua::shutdown() 
{
    lua_close(state);
}

bool Lua::runChunk(const char * chunk) 
{
    if (luaL_loadbuffer(state, chunk, strlen(chunk), chunk) != LUA_OK) {
        Scene::setText(lua_tostring(state, -1));
        return false;
    }
    if (lua_pcall(state, 0, 0, 0) != LUA_OK) {
        Scene::setText(lua_tostring(state, -1));
        return false;
    }
    return true;
}

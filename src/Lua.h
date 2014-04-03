#pragma once

#include "globals.h"

class Lua
{
public:
    static void init();
    static void shutdown();
    static bool runChunk(const char * chunk);

private:
    static lua_State * state;
    static void doFile(const char * pathname);
    static void throwError(int result);
    static bool displayError(int result);
};

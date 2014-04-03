#pragma once

#include "globals.h"

class Functions
{
public:
    static void init(lua_State * state);
    static int quit(lua_State * state);
    static int msgbox(lua_State * state);
    static int setbg(lua_State * state);

private:
};

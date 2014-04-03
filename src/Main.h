#pragma once

#include "globals.h"

class Main 
{
public:
    static SDL_Window * window;

    static void run();

private:
    static Uint32 previousMilliseconds;

    static void init();
    static void loop();
    static void shutdown();
    static void render();
    static void update();
};

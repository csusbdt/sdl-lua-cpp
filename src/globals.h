#pragma once

#include <iostream>
#include <sstream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "lua.hpp"

extern const char * APP_title;
extern const int APP_screenWidth; 
extern const int APP_screenHeight;
extern const SDL_Color APP_white;

void APP_throwSdlError(int result);

void APP_quit();
bool APP_isQuitting();

void APP_displayError(const char * errorMessage);

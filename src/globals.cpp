#include "globals.h"
#include "Main.h"

const char * APP_title = "CSE 441 Lua SDL Boilerplate";
const int APP_screenWidth = 800; 
const int APP_screenHeight = 640;

const SDL_Color APP_white = { 255, 255, 255 };

static bool APP_quitting = false;

void APP_throwSdlError(int result)
{
    if (result != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

void APP_quit()
{
	APP_quitting = true;
}

bool APP_isQuitting()
{
	return APP_quitting;
}

void APP_displayError(const char * errorMessage)
{
    SDL_ShowSimpleMessageBox(
	    SDL_MESSAGEBOX_ERROR,
    	APP_title,
    	errorMessage, 
    	Main::window);
    SDL_RaiseWindow(Main::window);
}

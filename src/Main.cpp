#include "globals.h"
#include "Input.h"
#include "Lua.h"
#include "Scene.h"
#include "Main.h"

int main(int argc, char ** argv)
{
    try 
    {
        Main::run();
    } 
    catch (std::runtime_error const & e) 
    {
        if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, APP_title, e.what(), nullptr) != 0) {
            std::cout << e.what();
        }
        return 1;
    }
    return 0;
}

SDL_Window * Main::window = nullptr;
Uint32 Main::previousMilliseconds;

void Main::run()
{
    init();
    loop();
    shutdown();
}

void Main::init() 
{
    APP_throwSdlError(SDL_Init(SDL_INIT_EVERYTHING));

    int desiredImageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    int resultingImageFlags = IMG_Init(desiredImageFlags);
    if ((desiredImageFlags & resultingImageFlags) != desiredImageFlags) {
        throw std::runtime_error("Required image support missing.");
    }

    if (TTF_Init() != 0) {
        throw std::runtime_error(TTF_GetError());
    }

    window = SDL_CreateWindow(
        APP_title, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        APP_screenWidth,
        APP_screenHeight,
        SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    
    // TODO: Read about and understand SDL_RENDERER_PRESENTVSYNC.
    // Maybe should have separate thread for AI/physics.
    // renderer = SDL_CreateRenderer(
    //     window,
    //     -1,
    //     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (renderer == nullptr) {
    //     throw new std::runtime_error(SDL_GetError());
    // }
    
    // // TODO: Read about SDL_RenderSetLogicalSize.
    // APP_throwSdlError(SDL_RenderSetLogicalSize(renderer, APP_screenWidth, APP_screenHeight));

    Scene::init(window);

    previousMilliseconds = SDL_GetTicks();

    Input::init();

    Lua::init();
}

void Main::loop() 
{
    while (true) {
        render();
        if (APP_isQuitting()) return;

        Input::processEventQueue();
        if (APP_isQuitting()) return;
        
        update();
        if (APP_isQuitting()) return;
    }
}

void Main::shutdown()
{
    Lua::shutdown();
    Scene::shutdown();
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();    
}

void Main::render()
{
    Scene::render();
}

void Main::update()
{
    Uint32 currentMilliseconds = SDL_GetTicks();
    double dt = (currentMilliseconds - previousMilliseconds) / 1000.0;
    previousMilliseconds = currentMilliseconds;
}

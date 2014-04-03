#include "globals.h"
#include "Font.h"
#include "Scene.h"

SDL_Renderer * Scene::renderer = nullptr;
SDL_Texture * Scene::backgroundTexture = nullptr;
Font * Scene::font = nullptr;
SDL_Texture * Scene::textTexture = nullptr;

void Scene::init(SDL_Window * window) 
{
    // TODO: Read about and understand SDL_RENDERER_PRESENTVSYNC.
    // Maybe should have separate thread for AI/physics.
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    
    // TODO: Read about SDL_RenderSetLogicalSize.
    APP_throwSdlError(SDL_RenderSetLogicalSize(renderer, APP_screenWidth, APP_screenHeight));

    font = new Font("fonts/DroidSansMono.ttf", 16);
}

void Scene::shutdown()
{
    if (backgroundTexture != nullptr) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    SDL_DestroyRenderer(renderer);
}

void Scene::render()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (backgroundTexture != nullptr) {
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    }
    if (textTexture != nullptr) {
        SDL_Rect dst;
        dst.x = 50;
        dst.y = 50;
        SDL_QueryTexture(textTexture, NULL, NULL, &dst.w, &dst.h);
        SDL_RenderCopy(renderer, textTexture, NULL, &dst);
    }

    SDL_RenderPresent(renderer);
}

void Scene::setBackground(const char * filename)
{
    if (backgroundTexture != nullptr) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = nullptr;
    }

    if (filename == nullptr) return;

    backgroundTexture = IMG_LoadTexture(Scene::renderer, filename);
    if (backgroundTexture == nullptr) {
        throw std::runtime_error(IMG_GetError());
    }
}

void Scene::setText(const std::string & text)
{
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    if (!text.empty()) {
        textTexture = font->makeTexture(renderer, APP_white, text.c_str());
    }
}


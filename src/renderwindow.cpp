#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Window failed to init. ERROR: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load a texture. Error: " << SDL_GetError() << std::endl;
    
    return texture;
}

int RenderWindow::getRefreshRate() {
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);
    
    return mode.refresh_rate;
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity) {
    SDL_Rect src;
    src.x = p_entity.getCurFrame().x;
    src.y = p_entity.getCurFrame().y;
    src.w = p_entity.getCurFrame().w;
    src.h = p_entity.getCurFrame().h;

    SDL_Rect dest;
    dest.x = p_entity.getPos().x * 2;
    dest.y = p_entity.getPos().y * 2;
    dest.w = p_entity.getCurFrame().w * 2;
    dest.h = p_entity.getCurFrame().h * 2;

    // SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
    SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dest, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::render(Entity& p_entity, float p_scale) {
    SDL_Rect src;
    src.x = p_entity.getCurFrame().x;
    src.y = p_entity.getCurFrame().y;
    src.w = p_entity.getCurFrame().w;
    src.h = p_entity.getCurFrame().h;

    SDL_Rect dest;
    dest.x = p_entity.getPos().x * p_scale;
    dest.y = p_entity.getPos().y * p_scale;
    dest.w = p_entity.getCurFrame().w * p_scale;
    dest.h = p_entity.getCurFrame().h * p_scale;

    // SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
    SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dest, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::render(Entity& p_entity, float p_scale, float p_rot) {
    SDL_Rect src;
    src.x = p_entity.getCurFrame().x;
    src.y = p_entity.getCurFrame().y;
    src.w = p_entity.getCurFrame().w;
    src.h = p_entity.getCurFrame().h;

    SDL_Rect dest;
    dest.x = p_entity.getPos().x * p_scale;
    dest.y = p_entity.getPos().y * p_scale;
    dest.w = p_entity.getCurFrame().w * p_scale;
    dest.h = p_entity.getCurFrame().h * p_scale;

    // SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dest);
    SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dest, p_rot, NULL, SDL_FLIP_NONE);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}

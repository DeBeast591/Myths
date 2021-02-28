#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>

#include "Math.hpp"

class Entity {
    public:
        Entity(Vector2f p_pos, SDL_Texture* p_texture);
        
        Vector2f& getPos() {
            return pos;
        }
        
        SDL_Texture* getTexture();
        SDL_Rect getCurFrame();
    
    private:
        Vector2f pos;
        SDL_Rect curFrame;
        SDL_Texture* texture;
};
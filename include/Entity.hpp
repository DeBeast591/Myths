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

        void setPos(Vector2f p_pos) {
            pos = p_pos;
        }

        void setVelX(int p_vel) {
            velx = p_vel;
        }

        void setVelY(int p_vel) {
            vely = p_vel;
        }

        void updatePos() {
            pos.x += velx;
            pos.y += vely;
        }

        float getSpeed() {
            return speed;
        }

        void setSpeed(float p_speed) {
            speed = p_speed;
        }
        
        SDL_Texture* getTexture();
        SDL_Rect getCurFrame();
    
    private:
        Vector2f pos;
        float velx = 0.0;
        float vely = 0.0;
        float speed;
        SDL_Rect curFrame;
        SDL_Texture* texture;
};
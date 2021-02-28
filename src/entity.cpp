#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_texture)
:pos(p_pos), texture(p_texture)
{
    curFrame.x = 0;
    curFrame.y = 0;
    curFrame.w = 32;
    curFrame.h = 32;
}

SDL_Texture* Entity::getTexture() {
    return texture;
}

SDL_Rect Entity::getCurFrame() {
    return curFrame;
}
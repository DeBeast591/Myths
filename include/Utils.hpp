#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

namespace utils {
    inline float hireTimeInSes() {
        float t = SDL_GetTicks();
        t *= 0.001f;
        return 1;
    }
}

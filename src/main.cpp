#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

// Main
int main(int argv, char* args[]) {
    std::cout << "Starting Myths." << std::endl;

    // oh no! an error!
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "ERROR!\tSDL_init HAS FAILED!\tERROR: " << SDL_GetError() << std::endl;
    }

    // oh no! another error!
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_Init HAS FAILED!\tERROR: " << SDL_GetError() << std::endl;

    // render the window
    RenderWindow window("Myths (DEV COPY) (vB_1.0)", 1200, 720);

    // most all of the variables
    int groundToRender = 59;

    // get window refresh rate
    //int windowRefreshRate = window.getRefreshRate();
    std::cout << "Display Refresh Rate: " << window.getRefreshRate() << std::endl;

    // images
    SDL_Texture* img_groundTexture = window.loadTexture("res/images/tiles/ground_general.png");

    // entities
    std::vector<Entity> entities = {};
    std::vector<Entity> ground = {};

    // gen all the ground entities
    int posx = 0;
    int posy = 0;
    for (int i = 0; i <= groundToRender; i++) {
        ground.push_back(Entity(Vector2f(posx, posy), img_groundTexture));
        posx += 30;
        if (posx >= 300) {
            posx = 0;
            posy += 30;
        }
    }

    // game running?
    bool gameRunning = true;

    // this thing
    SDL_Event event;

    // timeStep = {value} updates / second
    // if it equals "0.01" then its 100 updates / second
    // aka "delta time"
    const float timeStep = 0.01;
    // percent until the game should update
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSecs();

    // Loop
    while (gameRunning) {

        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeInSecs();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= timeStep) {
            // stopping the game
            if (!gameRunning) {
                break;
            }
            
            // get controls + events
            if (SDL_PollEvent(&event)) {
                if(event.type == SDL_WINDOWEVENT) {
                    if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        std::cout << "SDL Window Event - Close" << std::endl;
                        gameRunning = false;
                        break;
                    }
                }
            }

            accumulator -= frameTime;
        }
        

        // the time left until the accumulator fills up
        // in percent
        // const float alpha = accumulator / timeStep;

        // clean the window
        window.clear();

        // render everything
        for (Entity& e : ground) {
            window.render(e);
        }

        // update the window
        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / window.getRefreshRate()) {
            SDL_Delay(1000 / window.getRefreshRate());
        }

        // debug
        // std::cout << utils::hireTimeInSecs() << std::endl;
    }


    // stop the game
    std::cout << "Exiting..." << std::endl;
    window.cleanUp();
    SDL_Quit();
    std::cout << "Exited" << std::endl;
    return 0;
}

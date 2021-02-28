#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

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
    RenderWindow window("Myths (DEV COPY) (vB_1.0)", 1280, 720);

    // get window refresh rate
    //int windowRefreshRate = window.getRefreshRate();
    std::cout << "Display Refresh Rate: " << window.getRefreshRate() << std::endl;


    // images
    SDL_Texture* img_groundTexture = window.loadTexture("res/images/tiles/ground_general.png");

    // entities
    std::vector<Entity> entities = {
        Entity(Vector2f(0, 0), img_groundTexture),
        Entity(Vector2f(30, 0), img_groundTexture),
        Entity(Vector2f(60, 0), img_groundTexture)
    };

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
    float currentTime = utils::hireTimeInSes();

    // Loop
    while (gameRunning) {

        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeInSes();
        float frameTime = newTime - currentTime;

        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= timeStep) {
            // stopping the game
            if (!gameRunning) {
                break;
            }
            
            // get controls + events
            while (SDL_PollEvent(&event)) {
                // more stopping the game
                if (event.type == SDL_QUIT)
                    gameRunning = false;
                
                // event more stopping the game
                if (event.type == SDL_KEYDOWN)
                    gameRunning = false;
            }

            accumulator -= frameTime;
        }
        

        // the time left until the accumulator fills up
        // in percent
        // const float alpha = accumulator / timeStep;

        // clean the window
        window.clear();

        // render everything
        for (Entity& e : entities) {
            window.render(e);
        }

        // update the window
        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / window.getRefreshRate()) {
            SDL_Delay(1000 / window.getRefreshRate());
        }

        // std::cout << utils::hireTimeInSes() << std::endl;
    }


    // stop the game
    std::cout << "Exiting..." << std::endl;
    window.cleanUp();
    SDL_Quit();

    std::cout << "Exited" << std::endl;
    return 0;
}

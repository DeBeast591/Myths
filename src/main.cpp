#include <SDL2/SDL.h>
// #include <SDL2/SDL_events.h>
// #include <SDL2/SDL_hints.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_keycode.h>
// #include <SDL2/SDL_mouse.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_timer.h>
// #include <SDL2/SDL_video.h>

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
    RenderWindow window("Myths (DEV COPY) (vB_1.0)", 1280, 720);

    // most all of the variables
    int groundToRender = 590;

    // get window refresh rate
    //int windowRefreshRate = window.getRefreshRate();
    std::cout << "Display Refresh Rate: " << window.getRefreshRate() << std::endl;

    // images
    SDL_Texture* img_groundTexture = window.loadTexture("res/images/tiles/ground_general.png");
    SDL_Texture* img_playerTextureNormal = window.loadTexture("res/images/player/move/Player_Move_Normal.png");
    SDL_Texture* img_septicTank = window.loadTexture("res/images/tiles/septic_tank.gif");
    SDL_Texture* img_beta_exodus = window.loadTexture("res/images/weapons/guns/endgame/b_exodus.png");

    // entities
    std::vector<Entity> entities = {};
    std::vector<Entity> ground = {};
    std::vector<Entity> tiles = {};

    Entity player(Vector2f(100, 100), img_playerTextureNormal);
    player.setSpeed(2.0);
    Entity heldWeapon(Vector2f(player.getPos().x, player.getPos().y), img_beta_exodus);

    // gen all the ground entities
    int posx = 10;
    int posy = 0;
    for (int i = 0; i <= groundToRender; i++) {
        ground.push_back(Entity(Vector2f(posx, posy), img_groundTexture));
        posx += 30;
        if (posx >= 630) {
            posx = 10;
            posy += 30;
        }
    }

    // gen the tiles
    tiles.push_back(Entity(Vector2f(10, 0), img_septicTank));

    // game running?
    bool gameRunning = true;

    // this thing (event)
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

                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_a)
                        player.setVelX(-player.getSpeed());
                    if (event.key.keysym.sym == SDLK_d)
                        player.setVelX(player.getSpeed());
                    if (event.key.keysym.sym == SDLK_w)
                        player.setVelY(-player.getSpeed());
                    if (event.key.keysym.sym == SDLK_s)
                        player.setVelY(player.getSpeed());
                }

                if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_a)
                        player.setVelX(0);
                    if (event.key.keysym.sym == SDLK_d)
                        player.setVelX(0);
                    if (event.key.keysym.sym == SDLK_w)
                        player.setVelY(0);
                    if (event.key.keysym.sym == SDLK_s)
                        player.setVelY(0);
                }
            }

            // move the weapon
            heldWeapon.setPos(Vector2f((player.getPos().x * 3.5), (player.getPos().y * 3.5)));

            // debug
            // player.getPos().print();

            accumulator -= frameTime;
        }

        // mouse things
        int mx , my;
        SDL_GetMouseState(&mx,&my);
        Vector2f mouse;
        mouse.x = (float)mx;
        mouse.y =(float)my;
        // Vector2f aim = Vector2f(mouse.x - player.getPos().x, mouse.y - player.getPos().y);
        // Vector2f norm = Vector2f(aim.x / sqrt(pow(aim.x, 2) + sqrt(pow(aim.y,2)) ,aim.y / sqrt(pow(aim.x, 2) + pow(aim.y,2)));
        // norm.print();
        // float rot = (atan2f(mouse.y - player.getPos().y, mouse.x - player.getPos().x)) * (180.0f / 3.14);
        // player.Rotate((atan2f(events.mouseMove.y - player.getPos().y, events.mouseMove.x - player.getPos().x)) * (180.0f / 3.14);
        float rot = (atan2f(my - player.getPos().y,
                mx - player.getPos().x)
                ) * (180.0f / 3.14);
        

        // the time left until the accumulator fills up
        // in percent
        // const float alpha = accumulator / timeStep;

        // clean the window
        window.clear();

        // render everything
        for (Entity& e : ground)
            window.render(e);
        for (Entity& e : entities)
            window.render(e);
        for (Entity& e : tiles)
            window.render(e);
        window.render(player);
        // window.render(heldWeapon, 0.5);
        window.renderWithRotate(heldWeapon, rot);
        
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

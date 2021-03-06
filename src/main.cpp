#include <SDL2/SDL.h>
// #include <SDL2/SDL_events.h>
// #include <SDL2/SDL_hints.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_keycode.h>
// #include <SDL2/SDL_mouse.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_timer.h>
// #include <SDL2/SDL_video.h>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"


#define ARM_LEN     15


std::vector<Entity> genGround(SDL_Texture* texture) {
    std::vector<Entity> ground = {};
    // gen all the ground entities
    int posx = 10;
    int posy = 0;
    for (int i = 0; i <= 590; i++) {
        ground.push_back(Entity(Vector2f(posx, posy), texture));
        posx += 30;
        if (posx >= 630) {
            posx = 10;
            posy += 30;
        }
    }
    return ground;
}

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

    // get window refresh rate
    //int windowRefreshRate = window.getRefreshRate();
    std::cout << "Display Refresh Rate: " << window.getRefreshRate() << std::endl;

    // images
    SDL_Texture* img_groundTexture = window.loadTexture("res/images/tiles/xahanns_textures/xahann_stonetile.png");
    SDL_Texture* img_woodTexture = window.loadTexture("res/images/tiles/xahanns_textures/xahann_woodtile.png");
    SDL_Texture* img_playerTextureNormal = window.loadTexture("res/images/player/move/Player_Move_Normal.png");
    SDL_Texture* img_septicTank = window.loadTexture("res/images/tiles/beasts_textures/septic_tank.gif");
    SDL_Texture* img_beta_exodus = window.loadTexture("res/images/weapons/guns/endgame/beast_beta_exodus.png");

    // entities
    std::vector<Entity> entities = {};
    std::vector<Entity> ground = {};
    std::vector<Entity> tiles = {};

    Entity player(Vector2f(100, 100), img_playerTextureNormal);
    player.setSpeed(2.0);
    float weaponMoveScale = 4;
    Entity heldWeapon(Vector2f(player.getPos().x * weaponMoveScale + 64, player.getPos().y * weaponMoveScale + 32), img_beta_exodus);

    ground = genGround(img_groundTexture);

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

        int mx, my;
        float rot;

        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= timeStep) {
            // stopping the game
            if (!gameRunning) {
                break;
            }
            
            // get controls + events
            while (SDL_PollEvent(&event)) {
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
                    
                    if (event.key.keysym.sym == SDLK_SPACE)
                        ground = genGround(img_woodTexture);
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
                
                if (SDL_GetMouseState(&mx, &my) == 1) {
                    std::cout << "CLICK!" << std::endl;
                }
            }


            // debug
            // player.getPos().print();

            accumulator -= frameTime;
        }
        
        // the time left until the accumulator fills up
        // in percent
        // const float alpha = accumulator / timeStep;

        // clean the window
        window.clear();
        
        // update the player
        player.updatePos();
        // calculate weapon rotation
        SDL_GetMouseState(&mx, &my);
        rot = (atan2f(my - (2*player.getPos().y+32), mx - (2*player.getPos().x)-32)) * (180.0f / 3.14);
        // move the weapon
        //heldWeapon.setPos(Vector2f((player.getPos().x * weaponMoveScale + 64), (player.getPos().y * weaponMoveScale + 32)));
        heldWeapon.setPos(Vector2f(
            weaponMoveScale*(player.getPos().x+16-4 + ARM_LEN),
            weaponMoveScale*(player.getPos().y+16-4)
            ));

        // render everything
        for (Entity& e : ground)
            window.render(e);
        for (Entity& e : entities)
            window.render(e);
        for (Entity& e : tiles)
            window.render(e);
        window.render(player);
        // window.render(heldWeapon, 0.5);
        // SDL_Point playerMouseRotThingy = {player.getPos().getXInt(), player.getPos().getYInt()};
        SDL_Point playerMouseRotThingy = {
            static_cast<int>(heldWeapon.getCurFrame().w/4 - ARM_LEN*2),
            static_cast<int>(heldWeapon.getCurFrame().h/4)
        };
        window.renderRot(heldWeapon, 0.5, rot, &playerMouseRotThingy);
        
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

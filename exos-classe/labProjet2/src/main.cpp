#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Mur.h"

SDL_Window *win;
SDL_Renderer *renderer;
int windowW = 800, windowH = 600;

int main(int argc, char **args) {

    srand(time (NULL));

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(windowW, windowH, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);


    const Uint8 *state;

    SDL_FRect rect;
    rect.x = windowW / 4;
    rect.y = 0;
    rect.w = windowW / 10;
    rect.h = 4 * windowH / 6;
    Uint32 lastTimeMove;
    Uint32 currentTime;
    float velocity = 2;
    int deltaTime = 50;

    // If I make 2px (vel)                        -------------------> in 0.05s
    // I will make:  "2px * 3s / 0.05s = 120px"   <----------------- so en 3s

    // vel * 3s / 0.05s = windowH
    // vel * 3s = 0.05s * windowH
    // Pour 50ms/frame, vel = 0.05s * 600px / 3s;
    // vel = 10px / 50 ms; (pour faire 600px (windowH) en 3s)

    //Pour 1ms/frame, vel = 0.001s * 600px /3s;
    //vel = 0.2px / 1ms; (pour faire 600px (windowH) en 3s)

//    float posX = windowW / 4;
//    float posY = 0;
//    Mur *mur = new Mur(windowW, windowH, posX, posY, 2);

    std::vector <Mur*> murs;
    for (float i = 0; i <3; i++) {
        murs.push_back(new Mur(windowW, windowH, windowW/4 + i * windowW/4, 0, rand()%10 + 2));
    }

    SDL_Event event;
    while (isRunning) {
        //currentTime = SDL_GetTicks();

        //Clean window
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        SDL_RenderClear(renderer);


        //Event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        state = SDL_GetKeyboardState(nullptr);

        //Update objects
//        if (currentTime - lastTimeMove > deltaTime) {
//            rect.y += velocity;
//            if (rect.y > windowH - rect.h || rect.y < 0) {
//                velocity *= -1;
//            }
//            lastTimeMove = currentTime;
//        }

        //mur->update(SDL_GetTicks());
        for (Mur* mur : murs) {
            mur->update(SDL_GetTicks());
        }

        //Display objects
        //SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
        //SDL_RenderFillRect(renderer, &rect);
        //SDL_RenderFillRectF(renderer,&rect);

        //mur->display(renderer);
        for (Mur* mur : murs) {
            mur->display(renderer);
        }



        //Pause image
        SDL_Delay(1);
        //Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
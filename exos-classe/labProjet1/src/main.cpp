#include <SDL2/SDL.h>
#include "Player.h"

SDL_Window *win;
SDL_Renderer *render;
int windowW = 800, windowH = 600;
int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(windowW, windowH, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);


    const Uint8 *state;
    Player* player = new Player(windowW, windowH);

    SDL_Event event;
    while (isRunning) {

        //Clean window
        SDL_SetRenderDrawColor(render, 0, 128, 255, 255);
        SDL_RenderClear(render);


        //Event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        state = SDL_GetKeyboardState(nullptr);

        if (state[SDL_SCANCODE_LEFT]) {
            player->move(LEFT);;
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            player->move(RIGHT);;
        }

        if (state[SDL_SCANCODE_DOWN]) {
            player->move(DOWN);;
        }

        if (state[SDL_SCANCODE_UP]) {
            player->move(UP);
        }


        //Display objects
        player->display(render);


        //Pause image
        SDL_Delay(1);
        //Update screen
        SDL_RenderPresent(render);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
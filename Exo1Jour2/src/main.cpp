#include <iostream>
#include <SDL2/SDL.h>

SDL_Window* win;
SDL_Renderer* renderer;
int width = 800, height = 600;

int main(int argc, char** args) {

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);
    SDL_Event event;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 50;
    rect.h = 50;

    while (isRunning) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        SDL_PollEvent(&event);

        //loadBinaryFile();
        int nb = 1;
        if (nb == 1) {
            SDL_SetRenderDrawColor(renderer, 0,0,0,0);
            SDL_RenderFillRect(renderer, &rect);
        }

        if (nb== 0) {
            SDL_SetRenderDrawColor(renderer, 255,255,255,0);
        }


        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            isRunning = false;
        }

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

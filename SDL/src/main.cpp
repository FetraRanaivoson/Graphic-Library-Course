#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    SDL_Rect rectUp;
    rectUp.x = 0;
    rectUp.y = 0;
    rectUp.w = width;
    rectUp.h = height * 3 / 4;

    SDL_Rect rectBottom;
    rectBottom.x = 0;
    rectBottom.y = rectUp.h;
    rectBottom.w = width;
    rectBottom.h = height * 1 /4;

    SDL_Rect sliderBar;
    sliderBar.x = 20;
    sliderBar.y = rectUp.h + rectBottom.h * 1 / 2;
    sliderBar.w = width - sliderBar.x * 2;
    sliderBar.h = 2;

    SDL_Rect cursor;
    cursor.x = sliderBar.x;
    cursor.y = sliderBar.y;
    cursor.w = 20;
    cursor.y = 20;

    SDL_Event event;
    while (isRunning) {
        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        //dessin des différents objet dans la fenêtre
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
        SDL_RenderFillRect(renderer, &rectUp); //reference of the rectUp
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 0);
        SDL_RenderFillRect(renderer, &rectBottom);
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 0);
        SDL_RenderFillRect(renderer, &sliderBar);
        SDL_SetRenderDrawColor(renderer, 240, 10, 10, 0);
        SDL_RenderFillRect(renderer, &cursor);

        //pause dans l'image
        SDL_Delay(15);

        //mise a jour de l'écran
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();
    return 0;
}
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;

void CreateUI(SDL_Rect &rectUp, SDL_Rect &rectBottom, SDL_Rect &sliderBar, SDL_Rect &cursor);

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    SDL_Rect rectUp;
    SDL_Rect rectBottom;
    SDL_Rect sliderBar;
    SDL_Rect cursor;
    CreateUI(rectUp, rectBottom, sliderBar, cursor);

    SDL_Event event;
    const Uint8 *state = 0;

    std::vector<SDL_Rect *> rects;

    while (isRunning) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_PollEvent(&event);


        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
        SDL_RenderFillRect(renderer, &rectUp); //reference of the rectUp
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 0);
        SDL_RenderFillRect(renderer, &rectBottom);
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 0);
        SDL_RenderFillRect(renderer, &sliderBar);
        SDL_SetRenderDrawColor(renderer, 240, 10, 10, 100);
        SDL_RenderFillRect(renderer, &cursor);


        state = SDL_GetKeyboardState(NULL);

        srand((unsigned int) time(NULL));

        if (state[SDL_SCANCODE_RIGHT]) {
            cursor.x+= 5;
            //int nbSquare = 100 * (cursor.x - 20) / (sliderBar.w);

            SDL_Rect *rect  = new SDL_Rect();
            rect->x = rand() % width ;
            rect->y = rand() % height;
            rect->w = 10;
            rect->h = 10;

            rects.push_back(rect);
        }

        if (state[SDL_SCANCODE_ESCAPE])
            isRunning = false;

        if (state[SDL_SCANCODE_LEFT])
            cursor.x-=5;

        if (cursor.x < sliderBar.x)
            cursor.x = sliderBar.x;

        if (cursor.x > sliderBar.x + sliderBar.w)
            cursor.x = sliderBar.w;

        //std::cout << 100 * (cursor.x - 20) / (sliderBar.w) << std::endl;



        for (SDL_Rect *r : rects) {
            SDL_SetRenderDrawColor(renderer, rand()% 255, rand()% 255, rand()% 255, 0);
            SDL_RenderFillRect(renderer, r);
        }




        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();
    return 0;
}


void CreateUI(SDL_Rect &rectUp, SDL_Rect &rectBottom, SDL_Rect &sliderBar, SDL_Rect &cursor) {
    rectUp.x = 0;
    rectUp.y = 0;
    rectUp.w = width;
    rectUp.h = height * 3 / 4;

    rectBottom.x = 0;
    rectBottom.y = rectUp.h;
    rectBottom.w = width;
    rectBottom.h = height * 1 / 4;

    sliderBar.x = 20;
    sliderBar.y = rectUp.h + rectBottom.h * 1 / 2;
    sliderBar.w = width - sliderBar.x * 2;
    sliderBar.h = 2;

    cursor.x = sliderBar.x;
    cursor.y = sliderBar.y - 10;
    cursor.w = 10;
    cursor.h = 20;
}

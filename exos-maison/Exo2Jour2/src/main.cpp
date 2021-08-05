#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

#include <vector>

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;


void createMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                     SDL_Rect &yellowPencil);

void displayMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                      SDL_Rect &yellowPencil);

bool redPencilSelected(const SDL_Rect &redPencil, int x, int y);

bool bluePencilSelected(const SDL_Rect &bluePencil, int x, int y);

bool greenPencilSelected(const SDL_Rect &greenPencil, int x, int y);

bool yellowPencilSelected(const SDL_Rect &yellowPencil, int x, int y);

bool menuPanelSelected(const SDL_Rect &menuBar, int x, int y);

int main(int argc, char **args) {

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    SDL_Rect menuBar;
    SDL_Rect redPencil;
    SDL_Rect bluePencil;
    SDL_Rect greenPencil;
    SDL_Rect yellowPencil;
    createMenuPanel(menuBar, redPencil, bluePencil, greenPencil, yellowPencil);

    SDL_Log("%d, %d", redPencil.x, redPencil.w);

    SDL_Rect canvas;

    SDL_Event event;
    const Uint8 *state = 0;

    int x, y;
    int xx, yy;

    bool lineWasTraced = false;
    SDL_Rect rect;

    while (isRunning) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        displayMenuPanel(menuBar, redPencil, bluePencil, greenPencil, yellowPencil);


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                Uint32 buttons;
                SDL_PumpEvents();
                buttons = SDL_GetMouseState(&x, &y);

                if (redPencilSelected(redPencil, x, y)) {
                    SDL_Log("Red selected");
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                }

                if (bluePencilSelected(bluePencil, x, y)) {
                    SDL_Log("Blue selected");
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
                }


                if (greenPencilSelected(greenPencil, x, y)) {
                    SDL_Log("Green selected");
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
                }


                if (yellowPencilSelected(yellowPencil, x, y)) {
                    SDL_Log("Yellow selected");
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);

                }

//                if (menuPanelSelected(menuBar, x, y)) {
//                    SDL_Log("Click was inside menu panel");
//                }

            }

            if (event.type = SDL_MOUSEBUTTONUP) {
                Uint32 buttons2;
                SDL_PumpEvents();
                buttons2 = SDL_GetMouseState(&xx, &yy);
            }
        }

        SDL_RenderDrawLine(renderer, x, y, xx, yy);


        state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
            isRunning = false;

        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();
    return 0;
}

bool menuPanelSelected(const SDL_Rect &menuBar, int x, int y) {
    return x >= menuBar.x && x < menuBar.x + menuBar.w && y >= menuBar.y &&
           y < menuBar.y + menuBar.h;
}

bool yellowPencilSelected(const SDL_Rect &yellowPencil, int x, int y) {
    return x > yellowPencil.x
           && x < yellowPencil.x + yellowPencil.w
           && y > yellowPencil.y
           && y < yellowPencil.y + yellowPencil.h;
}

bool greenPencilSelected(const SDL_Rect &greenPencil, int x, int y) {
    return x > greenPencil.x
           && x < greenPencil.x + greenPencil.w
           && y > greenPencil.y
           && y < greenPencil.y + greenPencil.h;
}

bool bluePencilSelected(const SDL_Rect &bluePencil, int x, int y) {
    return x > bluePencil.x
           && x < bluePencil.x + bluePencil.w
           && y > bluePencil.y
           && y < bluePencil.y + bluePencil.h;
}

bool redPencilSelected(const SDL_Rect &redPencil, int x, int y) {
    return x > redPencil.x
           && x < redPencil.x + redPencil.w
           && y > redPencil.y
           && y < redPencil.y + redPencil.h;
}

void displayMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                      SDL_Rect &yellowPencil) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
    SDL_RenderFillRect(renderer, &menu);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &redPencil);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &bluePencil);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &greenPencil);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
    SDL_RenderFillRect(renderer, &yellowPencil);
}

void createMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                     SDL_Rect &yellowPencil) {
    menu.x = 0;
    menu.y = 0;
    menu.w = width / 10;
    menu.h = height;

    redPencil.x = 20;
    redPencil.y = 20;
    redPencil.w = menu.w / 2;
    redPencil.h = menu.w / 2;

    bluePencil.x = 20;
    bluePencil.y = redPencil.y + 60;
    bluePencil.w = menu.w / 2;
    bluePencil.h = menu.w / 2;

    greenPencil.x = 20;
    greenPencil.y = bluePencil.y + 60;
    greenPencil.w = menu.w / 2;
    greenPencil.h = menu.w / 2;

    yellowPencil.x = 20;
    yellowPencil.y = greenPencil.y + 60;
    yellowPencil.w = menu.w / 2;
    yellowPencil.h = menu.w / 2;
}




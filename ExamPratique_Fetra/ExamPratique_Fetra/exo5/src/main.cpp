#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "iostream"

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;

int main(int argc, char **args) {
    srand(time(NULL));

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    SDL_Surface *surfaceTemp = IMG_Load("./assets/coin.png");
    int wI, hI;

    SDL_Texture *coinImg = nullptr;
    if (!surfaceTemp) {
        SDL_Log("Coin image loading failed");
    } else {
        //Transform surface to texture
        coinImg = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
        //Once surface is loaded, keep track of its width and height (the *srRect)
        wI = surfaceTemp->w;
        hI = surfaceTemp->h;
    }

    //Now create a rectangle to initialize the size of the *srRect (source)
    SDL_Rect sourcePosition;
    sourcePosition.x = 0;
    sourcePosition.y = 0;
    sourcePosition.w = wI;
    sourcePosition.h = hI;

    //Create a rectangle for the size of the *drRect (screen)
    SDL_Rect screenPosition;
    screenPosition.x = rand() % width;
    screenPosition.y = rand() % height;
    screenPosition.w = wI / 2;
    screenPosition.h = hI /2;
    SDL_FreeSurface(surfaceTemp);


    const Uint8 *state = nullptr;
    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int deltaTime = 1500;

    SDL_Event event;
    while (isRunning) {
        currentTime = SDL_GetTicks();

        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        SDL_RenderClear(renderer);


        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        if (currentTime - lastUpdate > deltaTime) {
            screenPosition.x = rand() % width;
            screenPosition.y = rand() % height;
            lastUpdate = currentTime;
        }


        SDL_RenderCopy(renderer,coinImg, &sourcePosition, &screenPosition);


        //pause dans l'image
        SDL_Delay(15);


        //mise a jour de l'écran
        SDL_RenderPresent(renderer);
    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "iostream"
SDL_Window *win;
SDL_Renderer *render;
int width = 800, height = 600;


int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);

    //Image initialization workflow
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *surfaceTemp = IMG_Load("./assets/img.jpg");
    int wI, hI;

    SDL_Texture *paintingImg = nullptr;
    if (!surfaceTemp) {
        SDL_Log("Image loading failed");
    } else {
        //Transform surface to texture
        paintingImg = SDL_CreateTextureFromSurface(render, surfaceTemp);
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
    screenPosition.x = 0;
    screenPosition.y = 0;
    screenPosition.w = wI;
    screenPosition.h = hI;

    SDL_FreeSurface(surfaceTemp);

    const Uint32 *mouseState;


    SDL_Event event;


    while (isRunning) {

        //Clean window
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);

        //Event handling
        SDL_PollEvent(&event);

        if (event.type == SDL_MOUSEWHEEL) {
            SDL_Log(std::to_string (event.wheel.y).c_str());
            if (event.wheel.y < 0) { //Zoom out
                SDL_Log("Zoom out");
                screenPosition.w = screenPosition.w * -.99;
                screenPosition.h = screenPosition.h * -.99;

            }
            if (event.wheel.y > 0) { //Zoom in
                SDL_Log("Zoom in");
                screenPosition.w = screenPosition.w * .99;
                screenPosition.h = screenPosition.h * .99;

            }
            event.wheel.y = 0;
        }

        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        //Draw any objects
        //*sRect: source (surfaceTemp)
        //*dRect: screen (NULL if I want source image to always cover entire screen)
        SDL_RenderCopy(render, paintingImg, &sourcePosition, &screenPosition);



        //Pause image
        SDL_Delay(15);
        //Update screen
        SDL_RenderPresent(render);
    }

    SDL_DestroyTexture(paintingImg);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
                        
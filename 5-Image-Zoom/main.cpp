#define SDL_MAIN_HANDLED
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
    SDL_Surface *surfaceTemp = IMG_Load("./img.jpg");
    int wI, hI;

    SDL_Texture *paintingImg = nullptr;
    SDL_Texture *thumbnailImg = nullptr;
    if (!surfaceTemp) {
        SDL_Log("Image loading failed");
    } else {
        //Transform surface to texture
        paintingImg = SDL_CreateTextureFromSurface(render, surfaceTemp);
        thumbnailImg = SDL_CreateTextureFromSurface(render, surfaceTemp);
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


    SDL_Rect screenPositionThumbnail;
    screenPositionThumbnail.w = wI/5;
    screenPositionThumbnail.h = hI/5;
    screenPositionThumbnail.x = width -screenPositionThumbnail.w;
    screenPositionThumbnail.y = height -screenPositionThumbnail.h;


    SDL_FreeSurface(surfaceTemp);

    const Uint32 *mouseState;


    SDL_Event event;


    while (isRunning) {

        //Clean window
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);

        //Event handling
        //use while si no getStateMouse or getKeyboardState
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEWHEEL) {
                if (event.wheel.y > 0) // scroll up
                {
                    // Put code for handling "scroll up" here!
                    screenPosition.w += screenPosition.w / 5;
                    screenPosition.h += screenPosition.h / 5;
                    SDL_Log("scroll up %d ", event.wheel.y);
                } else if (event.wheel.y < 0) // scroll down
                {
                    screenPosition.w -= screenPosition.w / 5;
                    screenPosition.h -= screenPosition.h / 5;
                    SDL_Log("scroll down %d ", event.wheel.y);
                }

                if (event.wheel.x > 0) // scroll right
                {
                    SDL_Log("scroll right ");
                } else if (event.wheel.x < 0) // scroll left
                {
                    // ...
                    SDL_Log("scroll left ");
                }
            }
//            if (event.type == SDL_MOUSEWHEEL) {
//                SDL_Log("whhel : %d " , event.wheel.x > 0);
//                //            if (event.wheel.y < 0) { //Zoom out
//                //                SDL_Log("Zoom out");
//                //                screenPosition.w = screenPosition.w * -.99;
//                //                screenPosition.h = screenPosition.h * -.99;
//                //
//                //            }
//                //            if (event.wheel.y > 0) { //Zoom in
//                //                SDL_Log("Zoom in");
//                //                screenPosition.w = screenPosition.w * .99;
//                //                screenPosition.h = screenPosition.h * .99;
//                //
//                //            }
//                //            event.wheel.y = 0;
//            }

            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        //Draw any objects
        //*sRect: source (surfaceTemp)
        //*dRect: screen (NULL if I want source image to always cover entire screen)
        SDL_RenderCopy(render, paintingImg, &sourcePosition, &screenPosition);
        SDL_RenderCopy(render, thumbnailImg, &sourcePosition, &screenPositionThumbnail);


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
                        
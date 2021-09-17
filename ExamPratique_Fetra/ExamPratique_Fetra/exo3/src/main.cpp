#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "iostream"

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    SDL_Surface *surfaceTemp = IMG_Load("./assets/coin.png");
    int wI, hI;

    std::vector<SDL_Texture *> coinImages;
    SDL_Texture *coinImg = nullptr;
    //Transform surface to texture
    coinImg = SDL_CreateTextureFromSurface(renderer, surfaceTemp);

    if (!surfaceTemp) {
        SDL_Log("Coin image loading failed!");
    } else {
        for (int i = 0; i < 5; i++) {
            //coinImages.push_back(coinImg);
        }
        //Once surface is loaded, keep track of its width and height (the *srRect)
        wI = surfaceTemp->w;
        hI = surfaceTemp->h;
    }

    SDL_Rect sourcePosition;
    sourcePosition.x = 0;
    sourcePosition.y = 0;
    sourcePosition.w = wI;
    sourcePosition.h = hI;

    SDL_Rect screenPosition;
    screenPosition.w = width / 5;
    screenPosition.h = height / 2;
    int nextColumn = -1;
    screenPosition.x = nextColumn * width / 5;
    screenPosition.y = height / 2 - screenPosition.h / 2;

    SDL_FreeSurface(surfaceTemp);

    const Uint8 *state = nullptr;


    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int deltaTime = 250;

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

        state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_A]) {
            if (currentTime - lastUpdate > deltaTime) {
                coinImages.push_back(coinImg);
                lastUpdate = currentTime;
            }
        }

        else if (state[SDL_SCANCODE_D]) {
            if (currentTime - lastUpdate > deltaTime) {
                if (!coinImages.empty()) {
                    coinImages.pop_back();
                }
                lastUpdate = currentTime;
            }
        }


        for (int i = 0; i < coinImages.size(); i++) {
            screenPosition.x = i * width / 5;
            SDL_RenderCopy(renderer, coinImages[i], &sourcePosition, &screenPosition);
        }



        //pause dans l'image
        SDL_Delay(15);


        //mise a jour de l'écran
        SDL_RenderPresent(renderer);
    }


    for (SDL_Texture *coinImg: coinImages)
        SDL_DestroyTexture(coinImg);

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
                        
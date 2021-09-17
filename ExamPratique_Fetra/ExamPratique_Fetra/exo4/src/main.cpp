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

    SDL_Texture *sprite = IMG_LoadTexture(renderer, "./assets/trump_run.png");
    //Img
    int wI = 0, hI = 0;
    //Sprite
    int wS = 0, hS = 0;
    int col = 0, row = 0;
    SDL_QueryTexture(sprite, NULL, NULL, &wI, &hI);
    wS = wI / 6;
    hS = hI / 4;

    SDL_Rect positionDansImage = {col * wS, row * hS, wS, hS};
    SDL_Rect positionDansEcran = {0, 0, wS, hS};


    int velocity = 5;


    const Uint8 *state = nullptr;
    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int deltaTime = 75;

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
        if (state[SDL_SCANCODE_LEFT]) {
            row = 3;
            positionDansImage.y = row * hS;
            if (currentTime - lastUpdate > deltaTime) {
                col++;
                col %= 6;
                positionDansImage.x = col * wS;
                lastUpdate = currentTime;
            }
            positionDansEcran.x -= velocity;
            if (positionDansEcran.x < 0)
                positionDansEcran.x = 0;
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            row = 1;
            positionDansImage.y = row * hS;
            if (currentTime - lastUpdate > deltaTime) {
                col++;
                col %= 6;
                positionDansImage.x = col * wS;
                lastUpdate = currentTime;
            }
            positionDansEcran.x += velocity;
            if (positionDansEcran.x > width - positionDansEcran.w)
                positionDansEcran.x = width - positionDansEcran.w;
        }

        if (state[SDL_SCANCODE_DOWN]) {
            row = 0;
            positionDansImage.y = row * hS;
            if (currentTime - lastUpdate > deltaTime) {
                col++;
                col %= 6;
                positionDansImage.x = col * wS;
                lastUpdate = currentTime;
            }
            positionDansEcran.y += velocity;
            if (positionDansEcran.y > height- positionDansEcran.h)
                positionDansEcran.y = height - positionDansEcran.h;
        }

        if (state[SDL_SCANCODE_UP]) {
            row = 2;
            positionDansImage.y = row * hS;
            if (currentTime - lastUpdate > deltaTime) {
                col++;
                col %= 6;
                positionDansImage.x = col * wS;
                lastUpdate = currentTime;
            }
            positionDansEcran.y -= velocity;
            if (positionDansEcran.y < 0)
                positionDansEcran.y = 0;
        }

        SDL_RenderCopy(renderer, sprite, &positionDansImage, &positionDansEcran);




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
                        
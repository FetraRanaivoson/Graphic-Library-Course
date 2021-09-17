#include <SDL2/SDL.h>
#include <vector>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "Coin.h"
#include "iostream"
#include "Trump.h"

SDL_Window *win;
SDL_Renderer *renderer;
int windowWidth = 800, windowHeight = 600;


int main(int argc, char **args) {

    srand(time(NULL));

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win,
                                &renderer);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096);
    Mix_Chunk *bip = Mix_LoadWAV("./assets/coins.ogg");

    if (bip == NULL) {
        SDL_Log("Null");
    }

    //std::vector<Coin *> coins;
    Coin *coin = new Coin(renderer, windowWidth, windowHeight, rand() % windowWidth, rand() % windowHeight);
    //coins.push_back(coin);


    SDL_Texture *sprite = IMG_LoadTexture(renderer, "./assets/trump_run.png");
    int wS = 0, hS = 0;
    int col = 0, row = 0;
    int wI = 0, hI = 0;
    SDL_QueryTexture(sprite, NULL, NULL, &wI, &hI);
    wS = wI / 6;
    hS = hI / 4;
    SDL_Rect positionImg = {col * wS, row * hS, wS, hS};
    SDL_Rect positionScreen = {0, 0, wS , hS};
    //Trump* trump = new Trump(renderer);


    int velocity = 5;


    const Uint8 *state = nullptr;
    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int deltaTime = 75;

    SDL_Event event;
    while (isRunning) {
        currentTime = SDL_GetTicks();

        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(renderer, 158, 25, 34, 20);
        SDL_RenderClear(renderer);


        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        //dessin des différents objet dans la fenêtre
        state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_RIGHT]) {
            row = 1;
            positionImg.y = row * hS;

            if (currentTime - lastUpdate >= deltaTime) {
                col++;
                col %= 5;
                positionImg.x = col * wS;
                lastUpdate = currentTime;
            }
            positionScreen.x += velocity;
        }

        if (state[SDL_SCANCODE_LEFT]) {
            row = 3;
            positionImg.y = row * hS;

            if (currentTime - lastUpdate >= deltaTime) {
                col++;
                col %= 5;
                positionImg.x = col * wS;
                lastUpdate = currentTime;
            }
            positionScreen.x -= velocity;
        }

        if (state[SDL_SCANCODE_UP]) {
            row = 2;
            positionImg.y = row * hS;

            if (currentTime - lastUpdate >= deltaTime) {
                col++;
                col %= 5;
                positionImg.x = col * wS;
                lastUpdate = currentTime;
            }
            positionScreen.y -= velocity;
        }

        if (state[SDL_SCANCODE_DOWN]) {
            row = 0;
            positionImg.y = row * hS;

            if (currentTime - lastUpdate >= deltaTime) {
                col++;
                col %= 5;
                positionImg.x = col * wS;
                lastUpdate = currentTime;
            }
            positionScreen.y += velocity;
        }
        SDL_RenderCopy(renderer, sprite, &positionImg, &positionScreen);

        //trump->update(renderer);


        coin->update(renderer, SDL_GetTicks());



        //for (int i= 0; i < coins.size(); i++) {
        if (positionScreen.x + positionScreen.w > coin->getPositionScreenCoin().x
            && positionScreen.x < coin->getPositionScreenCoin().x + coin->getPositionScreenCoin().w
            && positionScreen.y + positionScreen.h > coin->getPositionScreenCoin().y
            && positionScreen.y < coin->getPositionScreenCoin().y + coin->getPositionScreenCoin().h) {
            // coins.erase(coins.cbegin() + i);
            Mix_PlayChannel(1, bip, 0);
        }
        //}


        //pause dans l'image
        SDL_Delay(15);
        //mise a jour de l'écran
        SDL_RenderPresent(renderer);
    }

    coin->destroy();
    Mix_FreeChunk(bip);
    SDL_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}


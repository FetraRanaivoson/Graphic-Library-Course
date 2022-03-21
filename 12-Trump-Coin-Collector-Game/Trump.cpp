//
// Created by Fetra on 8/16/2021.
//

#include "Trump.h"

Trump::Trump(SDL_Renderer* renderer) {


    sprite = IMG_LoadTexture(renderer, "./assets/trump_run.png");
    wS = 0, hS = 0;
    col = 0, row = 0;
    wI = 0, hI = 0;
    SDL_QueryTexture(sprite, NULL, NULL, &wI, &hI);
    wS = wI / 6;
    hS = hI / 4;
    positionImg = {col * wS, row * hS, wS, hS};
    positionScreen = {0, 0, wS , hS};



}

void Trump::update(SDL_Renderer* renderer) {
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
}

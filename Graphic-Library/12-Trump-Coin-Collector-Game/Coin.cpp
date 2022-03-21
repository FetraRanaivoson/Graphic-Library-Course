//
// Created by Fetra on 8/10/2021.
//

#include "Coin.h"

Coin::Coin(SDL_Renderer *renderer, int w, int h, int initPosX, int initPosY) {


    coinTexure = IMG_LoadTexture(renderer, "./assets/coin-sprite.png");
    colCoin = 0, rowCoin = 0;
    wCoinS = 0, hCoinS = 0;
    wIC = 0, hIC = 0;
    SDL_QueryTexture(coinTexure, NULL, NULL, &wIC, &hIC);

    wCoinS = wIC / 6;
    hCoinS = hIC;

    positionImgCoin = {colCoin * wCoinS, rowCoin * hCoinS, wCoinS, hCoinS};
    positionScreenCoin = {initPosX, initPosY, wCoinS / 2, hCoinS / 2};

    this->w = w;
    this->h = h;

}

void Coin::update(SDL_Renderer *renderer, Uint32 time) {


    if (time - lastUpdate >= deltaTime) {
        positionScreenCoin.x = rand() % w;
        positionScreenCoin.y = rand() % h;
        lastUpdate = time;

    }
    SDL_RenderCopy(renderer, coinTexure, &positionImgCoin, &positionScreenCoin);

}

void Coin::destroy() {
    SDL_DestroyTexture(coinTexure);
    IMG_Quit();
}

const SDL_Rect &Coin::getPositionScreenCoin() const {
    return positionScreenCoin;
}

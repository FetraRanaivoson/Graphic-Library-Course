//
// Created by Fetra on 8/10/2021.
//

#ifndef DEMOFIRSTSDL_COIN_H
#define DEMOFIRSTSDL_COIN_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class Coin {
    SDL_Texture *coinTexure;

    int colCoin = 0, rowCoin = 0;
    int wCoinS = 0, hCoinS = 0;
    int wIC =0, hIC =0;

    SDL_Rect positionImgCoin;
    SDL_Rect positionScreenCoin;

    Uint32 lastUpdate =0;
    int deltaTime = 1500;

    int w, h;
public:
    Coin(SDL_Renderer* renderer, int w, int h, int initPosX, int initPosY);

    void update(SDL_Renderer* renderer, Uint32 time);

    void destroy();

    const SDL_Rect &getPositionScreenCoin() const;
};


#endif //DEMOFIRSTSDL_COIN_H

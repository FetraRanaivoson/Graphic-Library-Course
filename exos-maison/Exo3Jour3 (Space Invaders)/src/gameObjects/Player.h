//
// Created by Fetra on 8/7/2021.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "iostream"
#include "Spaceship.h"

#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H


class Player: public Spaceship {


public:
    Player(SDL_Renderer *renderer, int windowW, int windowH, int initialPosX, int initialPosY);

    void initializeImage(SDL_Renderer *renderer, int windowW, int windowH) override;
    void display(SDL_Renderer *renderer) override;
    void update(Uint32 time) override;

    int getFriction() const override;

    int getFps() const override;

    void destroyResources() override;

};


#endif //SPACEINVADERS_PLAYER_H

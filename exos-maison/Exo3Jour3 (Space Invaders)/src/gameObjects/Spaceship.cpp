//
// Created by Fetra on 8/7/2021.
//

#include "Spaceship.h"

Spaceship::Spaceship(SDL_Renderer *renderer, int windowW, int windowH, int initialPosX, int initialPosY) {
    this->windowW = windowW;
    this->windowH = windowH;

    //initializeImage(renderer, windowW, windowH);

    state = SDL_GetKeyboardState(NULL);
    momentum = 0;
    acceleration = 0;
    friction = 0;

}

void Spaceship::setInitialPosX(int initialPosX) {
    this->initialPosX = initialPosX;
}

void Spaceship::setInitialPosY(int initialPosY) {
    this->initialPosY = initialPosY;
}



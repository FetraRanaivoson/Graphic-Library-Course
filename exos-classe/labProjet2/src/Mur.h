//
// Created by Fetra on 8/9/2021.
//

#ifndef LABPROJET1_MUR_H
#define LABPROJET1_MUR_H


#include <SDL2/SDL.h>

class Mur {
    SDL_FRect* position;
    int velocity;

    float posX, posY;

    float windowW, windowH;

    Uint32 lastTimeMove;
    int deltaTime;

public:
    Mur(float windowW, float windowH, float posX, float posY, int velocity);

    void display(SDL_Renderer* renderer);

    void update(Uint32 time);

};


#endif //LABPROJET1_MUR_H

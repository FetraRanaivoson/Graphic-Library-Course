//
// Created by Fetra on 8/7/2021.
//

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H


#include "Spaceship.h"

class Enemy : public Spaceship{
private:
    int refreshRate; //in ms
    SDL_RendererFlip flip;

public:
    Enemy(SDL_Renderer *renderer, int windowW, int windowH, int initialPosX, int initialPosY);

    void initializeImage(SDL_Renderer *renderer, int windowW, int windowH) override;
    void display(SDL_Renderer *renderer) override;
    void update(SDL_Renderer *renderer, Uint32 time) override;

    int getFriction() const override;

    int getFps() const override;

    void destroyResources() override;


    bool isTouchedBy(SDL_Rect ammo);



};


#endif //SPACEINVADERS_ENEMY_H

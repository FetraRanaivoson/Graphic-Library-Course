//
// Created by Fetra on 8/7/2021.
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "iostream"
#include <stdlib.h>
#include <time.h>

#ifndef SPACEINVADERS_SPACESHIP_H
#define SPACEINVADERS_SPACESHIP_H


class Spaceship {
protected:
    SDL_Surface *surfaceTemp;
    SDL_Texture *textureImg = nullptr;
    SDL_Rect screenPosition;
    SDL_Rect sourcePosition;
    int wI, hI;

    SDL_Rect ammo;

    int initialPosX;
    int initialPosY;

    int windowW, windowH;

    const Uint8 *state;
    int momentum;
    double velocity;
    int acceleration;
    int friction;

    Uint32 currentTime;
    Uint32 lastUpdate;
    double deltaTime;
    int fps;

public:
    Spaceship(SDL_Renderer *renderer, int windowW, int windowH, int initialPosX, int initialPosY);


    virtual void initializeImage(SDL_Renderer *renderer, int windowW, int windowH) = 0;
    virtual void display(SDL_Renderer *renderer) = 0;
    virtual void update(SDL_Renderer *renderer,Uint32 time) = 0;

    const SDL_Rect &getAmmo() const;

    void setInitialPosX(int initialPosX);
    void setInitialPosY(int initialPosY);

    virtual int getFriction() const = 0;

    virtual int getFps() const = 0;

    virtual void destroyResources() = 0;




};


#endif //SPACEINVADERS_SPACESHIP_H

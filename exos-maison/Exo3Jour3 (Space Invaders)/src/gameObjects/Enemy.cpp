//
// Created by Fetra on 8/7/2021.
//

#include "Enemy.h"


Enemy::Enemy(SDL_Renderer *renderer, int windowW, int windowH, int initialPosX, int initialPosY)
        : Spaceship(renderer, windowW, windowH, initialPosX, initialPosY){

    srand(time(NULL));

    this->initialPosX = initialPosX;
    this->initialPosY = initialPosY;

    refreshRate = 15;
    velocity = windowH * refreshRate / 5000;


}


void Enemy::initializeImage(SDL_Renderer *renderer, int windowW, int windowH) {
    surfaceTemp = IMG_Load("./assets/enemySpaceship.png");
    if (!surfaceTemp) {
        SDL_Log("Enemy image loading failed");
    } else {
        //Transform surface to texture
        textureImg = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
        //Once surface is loaded, keep track of its windowW and windowH (the *srRect)
        wI = surfaceTemp->w;
        hI = surfaceTemp->h;
    }

    //Now create a rectangle to initialize the size of the *srRect (source)
    sourcePosition.x = 0;
    sourcePosition.y = 0;
    sourcePosition.w = wI;
    sourcePosition.h = hI;

    //Create a rectangle for the size of the *drRect (screen)
    screenPosition.x = initialPosX;
    screenPosition.y = initialPosY;
    screenPosition.w = wI / 4;
    screenPosition.h = hI / 4;

    flip = SDL_FLIP_VERTICAL;
    SDL_FreeSurface(surfaceTemp);
}

void Enemy::display(SDL_Renderer *renderer) {
    //SDL_RenderCopy(renderer, textureImg, &sourcePosition, &screenPosition);
    SDL_RenderCopyEx(renderer, textureImg, &sourcePosition, &screenPosition, 0, 0, flip);
}

void Enemy::update(SDL_Renderer *renderer, Uint32 time) {

    currentTime = SDL_GetTicks();
    deltaTime = currentTime - lastUpdate;

    if (time - lastUpdate > refreshRate) {
        screenPosition.y += velocity;
        if (screenPosition.y > windowH)
            screenPosition.y = 0;

        lastUpdate = time;
    }

    //std::cout<<deltaTime<< std::endl;


//
//    deltaTime = currentTime - lastUpdate;
//    fps = 1000 / deltaTime;

}

int Enemy::getFriction() const {
    return 0;
}

int Enemy::getFps() const {
    return fps;
}

void Enemy::destroyResources() {
    SDL_DestroyTexture(textureImg);
    IMG_Quit();
}

bool Enemy::isTouchedBy(SDL_Rect ammo) {

    return ammo.x > screenPosition.x
    && ammo.x + ammo.w < screenPosition.x + screenPosition.w
    && ammo.y > screenPosition.y
    && ammo.y + ammo.h < screenPosition.y + screenPosition.h;
}




//
// Created by Fetra on 8/7/2021.
//

#include "Player.h"

Player::Player(SDL_Renderer *renderer, int windowW, int windowH, int initialPosX, int initialPosY)
: Spaceship(renderer, windowW, windowH, initialPosX, initialPosY) {
//    initialPosX = windowW / 2;
//    initialPosY = windowH - 90;
    //initializeImage(renderer, windowW, windowH);

    this->initialPosX = initialPosX;
    this->initialPosY = initialPosY;

    velocity = 1;

    currentTime = SDL_GetTicks();
}

void Player::initializeImage(SDL_Renderer *renderer, int windowW, int windowH) {
    surfaceTemp = IMG_Load("./assets/playerSpaceship.png");
    if (!surfaceTemp) {
        SDL_Log("Player image loading failed");
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
    screenPosition.w = wI / 6;
    screenPosition.h = hI / 6;
    SDL_FreeSurface(surfaceTemp);
}

void Player::update(Uint32 time) {

    if (state[SDL_SCANCODE_LEFT]) {
        screenPosition.x -= velocity * deltaTime;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        screenPosition.x += velocity * deltaTime;
    }
    if (screenPosition.x > windowW) {
        screenPosition.x = 0;
    }
    if (screenPosition.x < 0) {
        screenPosition.x = windowW;
    }

    //std::cout << deltaTime <<std::endl;

    currentTime = SDL_GetTicks();
    deltaTime = currentTime - lastUpdate;
    fps = 1000 / deltaTime;

}

void Player::display(SDL_Renderer *renderer) {
    lastUpdate = SDL_GetTicks();
    SDL_RenderCopy(renderer, textureImg, &sourcePosition, &screenPosition);
}

int Player::getFriction() const {
    return 0;
}

int Player::getFps() const {
    return fps;
}

void Player::destroyResources() {
    SDL_DestroyTexture(textureImg);
    IMG_Quit();
}




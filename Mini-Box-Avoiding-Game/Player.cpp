//
// Created by Fetra on 8/9/2021.
//

#include "Player.h"

Player::Player(int windowW, int windowH) {

    this->windowW = windowW;
    this->windowH = windowH;

    position = new SDL_Rect();
    *position = {0,windowH/2, 100, 100};

    velocity = .05;

    collideCount = 0;
}


void Player::move(Direction direction, double deltaTime) {
    if (direction == LEFT) {
        position->x -= velocity * deltaTime;
    }
    else if (direction == RIGHT) {
        position->x += velocity *deltaTime;
    }
    else if (direction == DOWN) {
        position->y += velocity * deltaTime;
    }
    else if (direction == UP) {
        position->y -= velocity * deltaTime;
    }
    if (position->x > windowW - position->w){
        position->x = windowW - position->w;
    }
    if (position->x < 0){
        position->x = 0;
    }

    if (position->y > windowH - position->h) {
        position->y = windowH - position->h;
    }

    if (position->y < 0) {
        position->y = 0;
    }

}

void Player::display(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderFillRect(renderer, position);
}

SDL_Rect *Player::getPosition() const {
    return position;
}



void Player::incrementCollideCount() {
    this->collideCount++;
}

int &Player::getCollideCount(){
    return collideCount;
}




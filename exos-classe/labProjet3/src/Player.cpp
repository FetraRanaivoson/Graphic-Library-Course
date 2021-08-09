//
// Created by Fetra on 8/9/2021.
//

#include "Player.h"

Player::Player(int windowW, int windowH) {

    this->windowW = windowW;
    this->windowH = windowH;

    position = new SDL_Rect();
    *position = {0,windowH/2, 100, 100};

    velocity = 1;
}


void Player::move(Direction direction) {
    if (direction == LEFT) {
        position->x -= velocity;
    }
    if (direction == RIGHT) {
        position->x += velocity;
    }
    if (direction == DOWN) {
        position->y += velocity;
    }
    if (direction == UP) {
        position->y -= velocity;
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


//
// Created by Fetra on 8/9/2021.
//

#include "Mur.h"

Mur::Mur(float windowW, float windowH, float posX, float posY, double velocity)
        : windowW(windowW), windowH(windowH),
          posX(posX), posY(posY),
          velocity(velocity) {

    position = new SDL_FRect();
    *position = {posX, posY, windowW / 10, 4 * windowH / 6};
    //velocity = 2;
    deltaTime = 50;
}

void Mur::display(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    SDL_RenderFillRectF(renderer, position);
}

void Mur::update(Uint32 time, double deltaTime) {

    //if (time - lastTimeMove > deltaTime) {
        position->y += velocity * deltaTime;
        if (position->y > windowH - position->h || position->y < 0) {
            velocity *= -1;
        }
        lastTimeMove = time;
    //}

}

bool Mur::isTouchedBy(Player *player) {

    return (player->getPosition()->x + player->getPosition()->w > position->x
            && player->getPosition()->x < position->x + position->w
            && player->getPosition()->y + player->getPosition()->h > position->y
            && player->getPosition()->y < position->y + position->h);
}

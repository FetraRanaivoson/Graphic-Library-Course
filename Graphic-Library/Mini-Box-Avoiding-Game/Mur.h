//
// Created by Fetra on 8/9/2021.
//

#include <SDL2/SDL.h>
#include "Player.h"

class Mur {
    SDL_FRect* position;
    double velocity;

    float posX, posY;

    float windowW, windowH;

    Uint32 lastTimeMove;
    int deltaTime;

public:
    Mur(float windowW, float windowH, float posX, float posY, double velocity);

    void display(SDL_Renderer* renderer);

    void update(Uint32 time, double deltaTime);

    bool isTouchedBy(Player* player);

};


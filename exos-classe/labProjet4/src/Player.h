//
// Created by Fetra on 8/9/2021.
//

#ifndef LABPROJET1_PLAYER_H
#define LABPROJET1_PLAYER_H


#include <SDL2/SDL.h>

enum Direction{LEFT, RIGHT, UP, DOWN};

class Player {
    SDL_Rect* position;
    int wI, hI;
    int velocity;

    int windowW, windowH;

    int collideCount;

public:
    Player(int windowW, int windowH);

    void move (Direction direction);
    void display(SDL_Renderer* renderer);

    SDL_Rect *getPosition() const;

    int& getCollideCount();

    void incrementCollideCount();
};


#endif //LABPROJET1_PLAYER_H

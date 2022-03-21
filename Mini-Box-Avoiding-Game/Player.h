//
// Created by Fetra on 8/9/2021.
//

#include <SDL2/SDL.h>
#include <vector>


enum Direction{LEFT, RIGHT, UP, DOWN};

class Player {


    SDL_Rect* position;
    int wI, hI;
    double velocity;

private:

    int windowW, windowH;
    int collideCount;

public:
    Player(int windowW, int windowH);

    void move (Direction direction, double deltaTime);
    void display(SDL_Renderer* renderer);

    SDL_Rect *getPosition() const;

    int& getCollideCount();

    void incrementCollideCount();
};

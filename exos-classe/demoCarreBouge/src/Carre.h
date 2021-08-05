//
// Created by jlidou on 2021-08-05.
//

#ifndef DEMOFIRSTSDL_CARRE_H
#define DEMOFIRSTSDL_CARRE_H

#include <SDL2/SDL.h>

class Carre {
private:
    SDL_Rect *position;
    SDL_Color *color;
    int velocityX;
    Uint32  lastTimeMove;
    int deltaTime;
public:
    Carre(int widthScreen, int heightScreen, int taille, SDL_Color *color);

    void draw(SDL_Renderer *renderer);

    void move(int widthScreen, Uint32 time);

    virtual ~Carre();

};


#endif //DEMOFIRSTSDL_CARRE_H

//
// Created by jlidou on 2021-08-05.
//

#include "Carre.h"

Carre::Carre(int widthScreen, int heightScreen, int taille, SDL_Color *color) : color(color) {
    position = new SDL_Rect();
    position->x = 0;
    position->y = heightScreen / 2;
    position->w = position->h = taille;

    deltaTime = 50;

    // refreshRate = 50ms/ frame  --->    velocity= 50 px
    // TimeAtWidthScreen ?         <---     widthScreen px
    // So TimeAtWidthScreen = widthScreen * refreshRate / velocity

    // If in 1000ms = widthScreen * refreshRate / Velocity
    // Either:
    // RefreshRate = Velocity * desiredTimeToBeAtWidth / widthScreen
    // OR Velocity = widthScreen * refreshRate / desiredTimeToBeAtWidth (in ms)
    velocityX = widthScreen * deltaTime / 1000;

}

void Carre::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer, position);
}

void Carre::move(int widthScreen, Uint32 time) {

    //sdl ticks: time since the program starts - lastTime move > delta time
    if (time - lastTimeMove > deltaTime) {

        position->x += velocityX;
        if (position->x > widthScreen)
            position->x = -position->w;

        lastTimeMove = time;
    }



//    position->x += velocityX;
//    if(position->x < 0 || position->x > widthScreen )
//        velocityX *=-1;

}

Carre::~Carre() {
    delete position;
}

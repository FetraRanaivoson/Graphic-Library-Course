//
// Created by Fetra on 8/9/2021.
//

#ifndef LABPROJET4_TEXTPRINTER_H
#define LABPROJET4_TEXTPRINTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "iostream"

class TextPrinter {
    int touchNumber;

    int windowW, windowH;

    TTF_Font *font;

    SDL_Surface *surfaceTextNbTouch;
    SDL_Texture *textToPrintNbTouch;

    SDL_Surface *surfaceTextMessage;
    SDL_Texture *textToPrintMessage;

    SDL_Surface *surfaceTextLabel;
    SDL_Texture *textToPrintLabel;

    int wText, hText;

    SDL_Rect positionTextureNbTouch;
    SDL_Rect positionTextureLabel;
    SDL_Rect positionTextureMessage;


public:
    TextPrinter(SDL_Renderer* renderer, int& touchNumber, int windowW, int windowH);

    void displayTouch(SDL_Renderer* renderer, int& touchNumber);

    void displayGameResult(SDL_Renderer* renderer, int& collideCount);

    void destroyResources();
};


#endif //LABPROJET4_TEXTPRINTER_H

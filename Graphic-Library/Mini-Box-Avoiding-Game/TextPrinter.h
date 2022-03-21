//
// Created by Fetra on 8/9/2021.
//

#ifndef LABPROJET4_TEXTPRINTER_H
#define LABPROJET4_TEXTPRINTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "iostream"
#include <string>

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

    SDL_Surface* surfaceTextFps;
    SDL_Texture* textToPrintFps;

    int wText, hText;

    SDL_Rect positionTextureNbTouch;
    SDL_Rect positionTextureLabel;
    SDL_Rect positionTextureMessage;
    SDL_Rect positionTextureFPS;


public:
    TextPrinter(SDL_Renderer* renderer, int& touchNumber, int windowW, int windowH);

    void displayTouch(SDL_Renderer* renderer, int& touchNumber);

    void displayFPS(SDL_Renderer* renderer, int& fps);

    void displayGameResult(SDL_Renderer* renderer, int& collideCount);



    void destroyResources();
};


#endif //LABPROJET4_TEXTPRINTER_H

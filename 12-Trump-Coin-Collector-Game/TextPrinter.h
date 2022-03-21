//
// Created by Fetra on 8/9/2021.
//


#ifndef TrumpTextPrinter_TextPrinter_H
#define TrumpTextPrinter_TextPrinter_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "iostream"
#include <string>

namespace TrumpTextPrinter {
    class TextPrinter {
        int score;

        int windowW, windowH;

        TTF_Font* font;

        SDL_Surface* surfaceTextScore;
        SDL_Texture* textToPrintScore;

        SDL_Surface* surfaceTextLabel;
        SDL_Texture* textToPrintLabel;

        int wText, hText;

        SDL_Rect positionTextureScore;
        SDL_Rect positionTextureLabel;


    public:
        TextPrinter(SDL_Renderer* renderer, int& score, int windowW, int windowH);

        void displayScore(SDL_Renderer* renderer, int& score);

        void displayFPS(SDL_Renderer* renderer, int& fps);

        void displayGameResult(SDL_Renderer* renderer, int& collideCount);

        ~TextPrinter();
    };
}

#endif

//
// Created by Fetra on 8/9/2021.
//

#include "TextPrinter.h"

TextPrinter::TextPrinter(SDL_Renderer* renderer, int& touchNumber, int windowW, int windowH)
        : touchNumber(touchNumber), windowW(windowW), windowH(windowH) {

    font = TTF_OpenFont("./consolab.ttf", 20);
    surfaceTextNbTouch = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 0});
    textToPrintNbTouch = SDL_CreateTextureFromSurface(renderer, surfaceTextNbTouch);
    //SDL_FreeSurface(surfaceTextNbTouch);

    surfaceTextLabel = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 0});
    textToPrintLabel = SDL_CreateTextureFromSurface(renderer, surfaceTextLabel);

    surfaceTextMessage = TTF_RenderUTF8_Blended(font, NULL, {255, 0, 0, 0});
    textToPrintMessage = SDL_CreateTextureFromSurface(renderer, surfaceTextMessage);

    surfaceTextFps = TTF_RenderUTF8_Blended(font, NULL, { 255, 0, 0, 0 });
    textToPrintFps = SDL_CreateTextureFromSurface(renderer, surfaceTextFps);


    wText= 20, hText = 20;
    SDL_QueryTexture(textToPrintNbTouch, NULL, NULL, &wText, &hText);
    SDL_QueryTexture(textToPrintLabel, NULL, NULL, &wText, &hText);
    SDL_QueryTexture(textToPrintMessage, NULL, NULL, &wText, &hText);
    SDL_QueryTexture(textToPrintFps, NULL, NULL, &wText, &hText);

    positionTextureLabel = {2, windowH - 50, wText + 60, hText};
    positionTextureNbTouch = {windowW / 9, windowH - 50, wText, hText};
    positionTextureMessage = {windowW / 5, windowH - 50, wText + 300, hText + 20};
    positionTextureFPS = { 0, 0, wText + 300, hText + 20 };

}

void TextPrinter::displayTouch(SDL_Renderer* renderer, int& touchNumber) {
    surfaceTextLabel = TTF_RenderUTF8_Blended(font, "Nb touch: ", {0, 0, 0, 255});
    textToPrintLabel = SDL_CreateTextureFromSurface(renderer, surfaceTextLabel);
    SDL_FreeSurface(surfaceTextLabel);
    SDL_RenderCopy(renderer, textToPrintLabel, NULL, &positionTextureLabel);
    

    surfaceTextNbTouch = TTF_RenderUTF8_Blended(font, std::to_string(touchNumber).c_str(), {0, 0, 0, 255});
    textToPrintNbTouch = SDL_CreateTextureFromSurface(renderer, surfaceTextNbTouch);
    SDL_FreeSurface(surfaceTextNbTouch);
    SDL_RenderCopy(renderer, textToPrintNbTouch, NULL, &positionTextureNbTouch);

}


void TextPrinter::displayFPS(SDL_Renderer* renderer, int& fps)
{
    std::string fpsText = "Fps: ";

    surfaceTextFps = TTF_RenderUTF8_Blended(font, (fpsText + std::to_string(fps)).c_str(), { 0,255,0,0 });
    textToPrintFps = SDL_CreateTextureFromSurface(renderer, surfaceTextFps);
    SDL_FreeSurface(surfaceTextFps);
    SDL_RenderCopy(renderer, textToPrintFps, NULL, &positionTextureFPS);
}


void TextPrinter::displayGameResult(SDL_Renderer* renderer, int& collideCount) {
    if (collideCount == 0)
        surfaceTextMessage = TTF_RenderUTF8_Blended(font, "Nice play, pas de touche!", {0, 255, 0, 255});
    else if (collideCount == 1 || collideCount == 2)
        surfaceTextMessage = TTF_RenderUTF8_Blended(font, "Win!", {0, 255, 0, 255});
    else
        surfaceTextMessage = TTF_RenderUTF8_Blended(font, "You lose, be careful next time!", {255, 0, 0, 255});

    textToPrintMessage = SDL_CreateTextureFromSurface(renderer, surfaceTextMessage);
    SDL_FreeSurface(surfaceTextMessage);
    SDL_RenderCopy(renderer, textToPrintMessage, NULL, &positionTextureMessage);
}


void TextPrinter::destroyResources() {
    SDL_DestroyTexture(textToPrintNbTouch);
    SDL_DestroyTexture(textToPrintLabel);
    TTF_CloseFont(font);
}


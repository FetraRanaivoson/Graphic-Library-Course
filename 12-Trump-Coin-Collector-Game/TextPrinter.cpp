//
// Created by Fetra on 8/9/2021.
//


#include "TextPrinter.h"
using namespace TrumpTextPrinter;

TextPrinter::TextPrinter(SDL_Renderer* renderer, int& score, int windowW, int windowH)
	: score(score), windowW(windowW), windowH(windowH) {

	TTF_Init();
	font = TTF_OpenFont("./assets/fontarcade.ttf", 20);
	if (font == NULL) {
		SDL_Log("NULL FONT");
	}
	surfaceTextScore = TTF_RenderUTF8_Blended(font, NULL, { 0, 0, 0, 0 });
	textToPrintScore = SDL_CreateTextureFromSurface(renderer, surfaceTextScore);
	//SDL_FreeSurface(surfaceTextNbTouch);

	surfaceTextLabel = TTF_RenderUTF8_Blended(font, NULL, { 0, 0, 0, 0 });
	textToPrintLabel = SDL_CreateTextureFromSurface(renderer, surfaceTextLabel);

	wText = 20, hText = 30;
	SDL_QueryTexture(textToPrintScore, NULL, NULL, &wText, &hText);
	SDL_QueryTexture(textToPrintLabel, NULL, NULL, &wText, &hText);

	positionTextureLabel = { 0, 0, wText + 60, hText };
	positionTextureScore = { windowW / 9, 0, wText, hText };


}

void TextPrinter::displayScore(SDL_Renderer* renderer, int& score) {
	surfaceTextLabel = TTF_RenderUTF8_Blended(font, "Score ", { 0, 255, 0, 255 });
	textToPrintLabel = SDL_CreateTextureFromSurface(renderer, surfaceTextLabel);
	SDL_FreeSurface(surfaceTextLabel);
	SDL_RenderCopy(renderer, textToPrintLabel, NULL, &positionTextureLabel);


	surfaceTextScore = TTF_RenderUTF8_Blended(font, std::to_string(score).c_str(), { 0, 255, 0, 255 });
	textToPrintScore = SDL_CreateTextureFromSurface(renderer, surfaceTextScore);
	SDL_FreeSurface(surfaceTextScore);
	SDL_RenderCopy(renderer, textToPrintScore, NULL, &positionTextureScore);

}

TextPrinter::~TextPrinter()
{
	SDL_DestroyTexture(textToPrintScore);
	SDL_DestroyTexture(textToPrintLabel);
	SDL_FreeSurface(surfaceTextLabel);
	SDL_FreeSurface(surfaceTextScore);
	TTF_CloseFont(font);
}


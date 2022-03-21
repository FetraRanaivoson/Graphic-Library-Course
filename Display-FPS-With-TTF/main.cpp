#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "iostream"
#include <string>

SDL_Window* win;
SDL_Renderer* render;
int width = 800, height = 600;

int main(int argc, char** args) {
	bool isRunning = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);

	TTF_Font* font = TTF_OpenFont("./bgothl.ttf", 20);

	SDL_Surface* surfaceTextFPS = TTF_RenderUTF8_Blended(font, "", { 0, 0, 0, 255 });
	SDL_Texture* textToPrintFPS = SDL_CreateTextureFromSurface(render, surfaceTextFPS);
	//SDL_FreeSurface(surfaceTextFPS);

	SDL_Surface* surfaceTextLabel = TTF_RenderUTF8_Blended(font, "", { 0, 0, 0, 255 });
	SDL_Texture* texToPrintLabel = SDL_CreateTextureFromSurface(render, surfaceTextLabel);
	//SDL_FreeSurface(surfaceTextLabel);

	int wText = 25, hText = 20;
	SDL_QueryTexture(textToPrintFPS, NULL, NULL, &wText, &hText);
	SDL_QueryTexture(texToPrintLabel, NULL, NULL, &wText, &hText);

	SDL_Rect positionTextureFPS = { width / 2, height - 30, wText, hText };
	SDL_Rect positionTextureLabel = { positionTextureFPS.x - wText, height - 30, wText, hText };



	SDL_Event event;

	SDL_Rect rect = { 10, height / 2, 50, 50 };
	const Uint8* state = nullptr;
	int rectVelocity = 1;

	Uint32 currentTime;
	currentTime = SDL_GetTicks();
	Uint32 lastUpdate;
	//int deltaTime;
	int deltaTime = 41.66; //Almost 24fps
	int fps = 0;

	while (isRunning) {
		//lastUpdate = currentTime; //or lastUpdate = SDL_GetTicks()

		//Nettoyer la fenêtre
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderClear(render);

		SDL_SetRenderDrawColor(render, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(render, &rect);

		//gestion évènement
		SDL_PollEvent(&event);
		state = SDL_GetKeyboardState(NULL);

		//        if (state [SDL_SCANCODE_RIGHT]) {
		//            rect.x += rectVelocity;
		//        }
		//        if (state[SDL_SCANCODE_LEFT]) {
		//            rect.x -= rectVelocity;
		//        }
		//        if (state [SDL_SCANCODE_DOWN]) {
		//            rect.y += rectVelocity;
		//        }
		//        if (state[SDL_SCANCODE_UP]) {
		//            rect.y -= rectVelocity;
		//        }

				//Vary deltaTime to change the fps
		if (state[SDL_SCANCODE_KP_PLUS]) { //Increase FPS
			if (deltaTime > 2)
				deltaTime--; //if fps = 1000 / deltaTime : the lesser the deltaTime, the greater FPS
		}
		if (state[SDL_SCANCODE_KP_MINUS]) { //Decrease FPS
			deltaTime++; //if fps = 1000 / deltaTime : the greater the deltaTime, the lesser FPS
		}


		rect.x += rectVelocity * deltaTime;
		if (rect.x - rect.w / 2 > width || rect.x < 0)
			rectVelocity *= -1;

		if (event.type == SDL_QUIT) {
			isRunning = false;
		}


		//dessin des différents objet dans la fenêtre
		surfaceTextFPS = TTF_RenderUTF8_Blended(font, std::to_string(fps).c_str(), { 0, 150, 0, 255 });
		textToPrintFPS = SDL_CreateTextureFromSurface(render, surfaceTextFPS);
		SDL_FreeSurface(surfaceTextFPS);
		SDL_RenderCopy(render, textToPrintFPS, NULL, &positionTextureFPS);


		surfaceTextLabel = TTF_RenderUTF8_Blended(font, "Fps: ", { 0, 150, 0, 255 });
		texToPrintLabel = SDL_CreateTextureFromSurface(render, surfaceTextLabel);
		SDL_FreeSurface(surfaceTextLabel);
		SDL_RenderCopy(render, texToPrintLabel, NULL, &positionTextureLabel);


		//pause dans l'image
		SDL_Delay(15);
		//mise a jour de l'écran
		SDL_RenderPresent(render);


		//currentTime = SDL_GetTicks();
		//deltaTime = currentTime - lastUpdate;
		fps = 1000 / deltaTime;
		std::cout << "Dt:" << deltaTime << "ms" << ", " << "fps: " << fps << std::endl;

		// 1fr  --> deltaTime (eg: 17 ms)
		// fps? <-- 1000ms (1s)
		// So fps = 1000 / deltaTime
		// The greater the deltaTime, the lesser the fps
		// The lesser the deltaTime, the greater the fps
		// So vary the deltaTime to change the fps
	}
	SDL_DestroyTexture(textToPrintFPS);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

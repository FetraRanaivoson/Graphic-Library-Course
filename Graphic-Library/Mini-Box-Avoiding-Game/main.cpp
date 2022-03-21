#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Mur.h"
#include "TextPrinter.h"

SDL_Window* win;
SDL_Renderer* renderer;
int windowW = 800, windowH = 600;

const int COLLIDER_COUNT = 3;


int main(int argc, char** args) {

	srand(time(NULL));

	bool isRunning = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_CreateWindowAndRenderer(windowW, windowH, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win,
		&renderer);

	//    TTF_Font *font = TTF_OpenFont("./assets/arial.ttf", 20);
	//    SDL_Surface *surfaceTextNbTouch = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 0});
	//    SDL_Texture *textToPrintNbTouch = SDL_CreateTextureFromSurface(renderer, surfaceTextNbTouch);
	//    //SDL_FreeSurface(surfaceTextNbTouch);
	//
	//    SDL_Surface *surfaceTextLabel = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 0});
	//    SDL_Texture *textToPrintLabel = SDL_CreateTextureFromSurface(renderer, surfaceTextLabel);
	//
	//
	//    int wText = 20, hText = 20;
	//    SDL_QueryTexture(textToPrintNbTouch, NULL, NULL, &wText, &hText);
	//    SDL_QueryTexture(textToPrintLabel, NULL, NULL, &wText, &hText);
	//
	//    SDL_Rect positionTextureNbTouch = {windowW / 9, windowH - 50, wText, hText};
	//    SDL_Rect positionTextureLabel = {2, windowH - 50, wText + 60, hText};
	int touchNumber = 0;
	TextPrinter* textPrinter = new TextPrinter(renderer, touchNumber, windowW, windowH);


	Uint32 timesNow = SDL_GetTicks();
	Uint32 lastTouchNumberUpdate = 0;
	int refreshTime = 250;


	const Uint8* state;

	SDL_FRect rect;
	rect.x = windowW / 4;
	rect.y = 0;
	rect.w = windowW / 10;
	rect.h = 4 * windowH / 6;
	//    Uint32 lastTimeMove;
	//    Uint32 currentTime;
	//    float velocity = 2;
	//    int deltaTime = 50;

		// If I make 2px (vel)                        -------------------> in 0.05s
		// I will make:  "2px * 3s / 0.05s = 120px"   <----------------- so en 3s

		// vel * 3s / 0.05s = windowH
		// vel * 3s = 0.05s * windowH
		// Pour 50ms/frame, vel = 0.05s * 600px / 3s;
		// vel = 10px / 50 ms; (pour faire 600px (windowH) en 3s)

		//Pour 1ms/frame, vel = 0.001s * 600px /3s;
		//vel = 0.2px / 1ms; (pour faire 600px (windowH) en 3s)

	std::vector<Mur*> murs;
	for (float i = 0; i < 3; i++) {
		double f = (double)rand() / RAND_MAX;
		double velocity = .01 + f * (.02 - .01);
		murs.push_back(new Mur(windowW, windowH, windowW / 4 + i * windowW / 4, 0, velocity));
	}

	Player* player = new Player(windowW, windowH);
	bool lose = false;
	double deltaTime = 41.66; //Almost 24fps
	int fps = 0;

	SDL_Event event;
	while (isRunning) {
		//currentTime = SDL_GetTicks();
		timesNow = SDL_GetTicks();

		//Clean window
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderClear(renderer);


		//Event handling
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			isRunning = false;
		}

		state = SDL_GetKeyboardState(nullptr);

		//Update objects
		for (Mur* mur : murs) {
			mur->update(SDL_GetTicks(), deltaTime);
		}

		//  Changing FPS
		if (state[SDL_SCANCODE_KP_PLUS]) { //Increase FPS
			if (deltaTime > 2)
				deltaTime--; //if fps = 1000 / deltaTime : the lesser the deltaTime, the greater FPS
		}
		if (state[SDL_SCANCODE_KP_MINUS]) { //Decrease FPS
			deltaTime++; //if fps = 1000 / deltaTime : the greater the deltaTime, the lesser FPS
		}



		if (!lose) {
			if (state[SDL_SCANCODE_LEFT]) {
				player->move(LEFT, deltaTime);
				if (timesNow - lastTouchNumberUpdate > refreshTime) {
					touchNumber++;
					lastTouchNumberUpdate = timesNow;
				}
			}

			if (state[SDL_SCANCODE_RIGHT]) {
				player->move(RIGHT, deltaTime);
				if (timesNow - lastTouchNumberUpdate > refreshTime) {
					touchNumber++;
					lastTouchNumberUpdate = timesNow;
				}

			}

			if (state[SDL_SCANCODE_DOWN]) {
				player->move(DOWN, deltaTime);
				if (timesNow - lastTouchNumberUpdate > refreshTime) {
					touchNumber++;
					lastTouchNumberUpdate = timesNow;
				}
			}

			if (state[SDL_SCANCODE_UP]) {
				player->move(UP, deltaTime);
				if (timesNow - lastTouchNumberUpdate > refreshTime) {
					touchNumber++;
					lastTouchNumberUpdate = timesNow;
				}
			}
		}


		//Display objects
		player->display(renderer);
		for (Mur* mur : murs) {
			mur->display(renderer);
		}

		//Game information
//        surfaceTextLabel = TTF_RenderUTF8_Blended(font, "Nb touch: ", {0, 0, 0, 255});
//        textToPrintLabel = SDL_CreateTextureFromSurface(renderer, surfaceTextLabel);
//        SDL_FreeSurface(surfaceTextLabel);
//        SDL_RenderCopy(renderer, textToPrintLabel, NULL, &positionTextureLabel);
//
//        surfaceTextNbTouch = TTF_RenderUTF8_Blended(font, std::to_string(touchNumber).c_str(), {0, 0, 0, 255});
//        textToPrintNbTouch = SDL_CreateTextureFromSurface(renderer, surfaceTextNbTouch);
//        SDL_FreeSurface(surfaceTextNbTouch);
//        SDL_RenderCopy(renderer, textToPrintNbTouch, NULL, &positionTextureNbTouch);
		textPrinter->displayTouch(renderer, touchNumber);
		textPrinter->displayFPS(renderer, fps);

		//Check intersection
		for (int i = 0; i < murs.size(); i++) {
			if (murs[i]->isTouchedBy(player)) {
				SDL_Log("Touched");
				murs.erase(murs.cbegin() + i);
				player->incrementCollideCount();
			}
		}


		//Win? Lose?
		if (player->getPosition()->x >= windowW - player->getPosition()->w) {
			textPrinter->displayGameResult(renderer, player->getCollideCount());
			lose = true;
		}

		fps = 1000 / deltaTime;
		std::cout << "Dt:" << deltaTime << "ms" << ", " << "fps: " << fps << std::endl;
		// 1fr  --> deltaTime (eg: 17 ms)
		// fps? <-- 1000ms (1s)
		// So fps = 1000 / deltaTime
		// The greater the deltaTime, the lesser the fps
		// The lesser the deltaTime, the greater the fps
		// So vary the deltaTime to change the fps

		//Pause image
		SDL_Delay(1);
		//Update screen
		SDL_RenderPresent(renderer);

	}

	textPrinter->destroyResources();
	//SDL_DestroyTexture(textToPrintNbTouch);
	//SDL_DestroyTexture(textToPrintLabel);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	//TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}



#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "iostream"

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;
int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();


    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    TTF_Font *font = TTF_OpenFont("./assets/fontarcade.ttf", 200);
    SDL_Surface *secondSurfaceText = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 255});
    SDL_Texture *secondText = SDL_CreateTextureFromSurface(renderer, secondSurfaceText);

    SDL_Surface *colonSurfaceText = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 255});
    SDL_Texture *colonText = SDL_CreateTextureFromSurface(renderer, colonSurfaceText);

    SDL_Surface *minuteSurfaceText = TTF_RenderUTF8_Blended(font, NULL, {0, 0, 0, 255});
    SDL_Texture *minuteText = SDL_CreateTextureFromSurface(renderer, minuteSurfaceText);

    int wText = 300, hText = 500;
    SDL_QueryTexture(secondText, NULL, NULL, &wText, &hText);
    SDL_QueryTexture(minuteText, NULL, NULL, &wText, &hText);

    int colonW = 15, colonH = 15;
    SDL_QueryTexture(colonText, NULL, NULL, &colonW, &colonH);

    SDL_Rect secondPositionTexture = {width / 2, height / 2- hText/2, wText, hText};
    SDL_Rect minutePositionTexture = {width/2 - 350, height / 2 - hText/2, wText, hText};
    SDL_Rect colonPositionTexture = {width / 2 - 50, height / 2 , colonW, colonH};


    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int deltaTime = 1000; //1s
    int second = 0;
    int minute = 0;

    SDL_Event event;
    while (isRunning) {
        currentTime = SDL_GetTicks();


        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        SDL_RenderClear(renderer);

        if (currentTime - lastUpdate > deltaTime) {
            second ++;
            lastUpdate = currentTime;
        }

        if (second == 59) {
            minute ++;
            second = 0;
        }


        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }



        //dessin des différents objet dans la fenêtre
        secondSurfaceText = TTF_RenderUTF8_Blended(font, std::to_string(second).c_str(), {255, 255, 255, 255});
        secondText = SDL_CreateTextureFromSurface(renderer, secondSurfaceText);
        SDL_FreeSurface(secondSurfaceText);
        SDL_RenderCopy(renderer, secondText, NULL, &secondPositionTexture);


        std::string sc = ":";
        colonSurfaceText = TTF_RenderUTF8_Blended(font, sc.c_str(), {255, 255, 255, 255});
        colonText = SDL_CreateTextureFromSurface(renderer, colonSurfaceText);
        SDL_FreeSurface(colonSurfaceText);
        SDL_RenderCopy(renderer, colonText, NULL, &colonPositionTexture);



        minuteSurfaceText = TTF_RenderUTF8_Blended(font, std::to_string(minute).c_str(), {255, 255, 255, 255} );
        minuteText = SDL_CreateTextureFromSurface(renderer, minuteSurfaceText);
        SDL_RenderCopy(renderer, minuteText, NULL, &minutePositionTexture);

        //pause dans l'image
        SDL_Delay(15);


        //mise a jour de l'écran
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(secondText);
    SDL_DestroyTexture(minuteText);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
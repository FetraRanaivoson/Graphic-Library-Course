#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "Carre.h"

SDL_Window *win;
SDL_Renderer *render;
int width = 800, height = 600;

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);
    SDL_Color color = {255, 100, 0, 255};
    Carre *monCarre = new Carre(width, height, 150, &color);


    SDL_Event event;
    while (isRunning) {
        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(render, 0, 128, 255, 255);
        SDL_RenderClear(render);
        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        // mise a jour de la position
        monCarre->move(width, SDL_GetTicks());

        //dessin des différents objet dans la fenêtre

        monCarre->draw(render);

        //pause dans l'image
        SDL_Delay(1);
        //mise a jour de l'écran
        SDL_RenderPresent(render);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;
int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);


    SDL_Texture *topLeft = IMG_LoadTexture(renderer, "./assets/red.jpg");
    SDL_Texture *topRight = IMG_LoadTexture(renderer, "./assets/green.jpg");
    SDL_Texture *bottom = IMG_LoadTexture(renderer, "./assets/blue.jpg");

    //Top left corner viewport
    SDL_Rect topLeftViewport;
    topLeftViewport.x = 0;
    topLeftViewport.y = 0;
    topLeftViewport.w = width / 2;
    topLeftViewport.h = height / 5;

    //Top right viewport
    SDL_Rect topRightViewport;
    topRightViewport.x = width / 2;
    topRightViewport.y = 0;
    topRightViewport.w = width/ 2;
    topRightViewport.h = height / 5;

    //Bottom viewport
    SDL_Rect bottomViewport;
    bottomViewport.x = 0;
    bottomViewport.y = height - height /5 ;
    bottomViewport.w = width;
    bottomViewport.h = height;


    SDL_Event event;
    while (isRunning) {
        //Nettoyer la fenêtre
        SDL_SetRenderDrawColor(renderer, 0, 128, 255, 255);
        SDL_RenderClear(renderer);



        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        //dessin des différents objet dans la fenêtre
        SDL_RenderSetViewport(renderer, &topLeftViewport);
        SDL_RenderCopy(renderer  , topLeft, NULL, NULL );

        SDL_RenderSetViewport(renderer, &topRightViewport );
        SDL_RenderCopy( renderer, topRight, NULL, NULL );


        SDL_RenderSetViewport( renderer, &bottomViewport );
        SDL_RenderCopy( renderer, bottom, NULL, NULL );



        //pause dans l'image
        SDL_Delay(15);


        //mise a jour de l'écran
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyTexture(topLeft);
    SDL_DestroyTexture(topRight);
    SDL_DestroyTexture(bottom);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
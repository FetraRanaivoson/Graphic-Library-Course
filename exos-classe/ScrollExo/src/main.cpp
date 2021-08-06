#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>;

SDL_Window *win;
SDL_Renderer *render;
int width = 800, height = 600;
int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);

    TTF_Font *font = TTF_OpenFont("./assets/.ttf", 20);

    SDL_Texture *bgSmall = IMG_LoadTexture(render, "./assets/bgSmall.png");

    int wI, hI;
    Uint32 format;
    SDL_QueryTexture(bgSmall,&format, NULL, &wI, &hI );
    SDL_Texture * bigBg = SDL_CreateTexture(render,  format,
                                            SDL_TEXTUREACCESS_TARGET,
                                            3*wI, hI);

    SDL_SetTextureBlendMode(bigBg, SDL_BLENDMODE_BLEND);

    //copier 3 times image
    SDL_SetRenderTarget(render, bigBg); //cibler ma texture ou je vais copier
    SDL_Rect position = {0,0, wI, hI};
    SDL_RenderCopy(render, bgSmall, NULL, &position);
    position.x += wI;
    SDL_RenderCopyEx(render, bgSmall, NULL, &position, 0, NULL, SDL_FLIP_HORIZONTAL);
    position.x += wI;


    SDL_SetRenderTarget(render, NULL);
    position.x = 0;

    Uint64  state;

    SDL_Event event;
    while (isRunning) {
        SDL_SetRenderDrawColor(render, 0, 128, 255, 255);
        SDL_RenderClear(render);

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        //state = SDL_GetKeyboardState(NULL);

        SDL_RenderCopy(render,bigBg, &position, NULL);


        SDL_Delay(1);
        SDL_RenderPresent(render);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();

    return 0;
}
                        